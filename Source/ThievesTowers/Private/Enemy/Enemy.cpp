#include "Enemy/Enemy.h"
#include "Manager/GA_ThievesTowers.h"
#include "Path.h"
#include "Engine/DamageEvents.h"
#include "PaperSpriteComponent.h"
#include "Components/SplineComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

//////////////////////////////////////////////////////////////////////////
/// AEnemy - Constructor
//////////////////////////////////////////////////////////////////////////
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SceneComponent->Mobility = EComponentMobility::Movable;
	RootComponent = SceneComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->CastShadow = true;
}


void AEnemy::InitializeEnemy(APath* NewPath, float NewCurrentDistance)
{
	Life = MaxLife;
	StartLife = MaxLife;
	this->CurrentPath = NewPath;
	this->CurrentPathDistance = NewCurrentDistance;
	this->TraveledDistance = NewCurrentDistance;
	this->CurrentPathLength = NewPath->GetSplineComponent()->GetSplineLength();

	APath* ptr = CurrentPath; this->TotalDistance = 0.0f;
	while (ptr) { TotalDistance += ptr->GetSplineComponent()->GetSplineLength(); ptr = ptr->GetNextPath(); }

	DynamicMaterial = Cast<UMaterialInstanceDynamic>(SpriteComponent->CreateAndSetMaterialInstanceDynamic(0));

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance->AddEnemy(this); }
}

//////////////////////////////////////////////////////////////////////////
/// AEnemy - Protected Methods
//////////////////////////////////////////////////////////////////////////
void AEnemy::MoveAlongPath(float DeltaTime)
{
	if (CurrentPath)
	{
		CurrentPathDistance += Speed * DeltaTime; TraveledDistance += Speed * DeltaTime;
		if (CurrentPathDistance > CurrentPathLength)
		{
			CurrentPathDistance -= CurrentPathLength;
			CurrentPath = CurrentPath->GetNextPath();
			if (!CurrentPath) { Die(false); return; }
			CurrentPathLength = CurrentPath->GetSplineComponent()->GetSplineLength();
		}

		SetActorLocation(CurrentPath->GetSplineComponent()->GetLocationAtDistanceAlongSpline(CurrentPathDistance, ESplineCoordinateSpace::World));
		SetActorRotation(CurrentPath->GetSplineComponent()->GetRotationAtDistanceAlongSpline(CurrentPathDistance, ESplineCoordinateSpace::World));
	}
	else { Die(false); }
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (LifeOverflows > 0)
	{
		LifeOverflows-= DamageAmount;
		if (LifeOverflows <= 0) { Life += LifeOverflows; LifeOverflows = 0; }
	}
	else { Life -= DamageAmount; }
	
	if (Life <= 0.0f) { Die(true); }
	return DamageAmount;
}

void AEnemy::Die(bool bExecuteByTower)
{
	//for (AProjectile* Projectile : Projectiles) { if (IsValid(Projectile)) { Projectile->Destroy(); } }
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		GameInstance->RemoveEnemy(this);
		if (bExecuteByTower) { GameInstance->GetMapManager()->AddGold(StartLife); }
		else { GameInstance->GetMapManager()->AddLife(-Damage); }
	}
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
/// AEnemy - Public Methods
//////////////////////////////////////////////////////////////////////////
void AEnemy::Heal(int HealAmount)
{
	if (HealAmount > 0 && Life + HealAmount <= MaxLife) { Life += HealAmount; }
	else { Life = MaxLife; }
	RemainingHealTime = HealEffectTime;
	DynamicMaterial->SetVectorParameterValue(FName("Color"), HealColor);
}

void AEnemy::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage)
	{
		if (!Resistances.Contains(TypeOfDamage))
		{
			TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
			return;
		}
	}
	
}

void AEnemy::Freeze(float FreezeTime, FColor FreezeColor, int NewDamageAfterFreeze, TArray<TEnumAsByte<ETypeOfDamage>> NewTypesOfDamage)
{
	RemainingFreezeTime = FreezeTime;
	DamageAfterFreeze = NewDamageAfterFreeze;
	FreezeTypesOfDamage = NewTypesOfDamage;
	
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName("Alpha"), 0.0f);
		DynamicMaterial->SetVectorParameterValue(FName("Color"), FreezeColor);
	}
}

//////////////////////////////////////////////////////////////////////////
///	AEnemy - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RemainingFreezeTime > 0.0f)
	{
		RemainingFreezeTime -= DeltaTime;
		if (RemainingFreezeTime <= 0.0f && DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(FName("Alpha"), 1.0f);
			if (DamageAfterFreeze > 0) { TakeDamage(DamageAfterFreeze, FreezeTypesOfDamage, FDamageEvent(), nullptr, this); }
			DamageAfterFreeze = 0;
			FreezeTypesOfDamage.Empty();
		}
		return;
	}
	if (RemainingHealTime > 0.0f)
	{
		RemainingHealTime -= DeltaTime;
		float HealPercent = RemainingHealTime / HealEffectTime;
		if (RemainingHealTime > 0) { DynamicMaterial->SetScalarParameterValue(FName("Alpha"), FMath::Lerp(1.0f, HealEffectAlpha, HealPercent)); }
		else { DynamicMaterial->SetScalarParameterValue(FName("Alpha"), 1.0f); }
	}
	MoveAlongPath(DeltaTime);
}