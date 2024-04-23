#include "Enemy.h"

#include "Path.h"
#include "Projectile.h"
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
	Health = StartHealth;
	this->CurrentPath = NewPath;
	this->CurrentPathDistance = NewCurrentDistance;
	this->TraveledDistance = NewCurrentDistance;
	this->CurrentPathLength = NewPath->GetSplineComponent()->GetSplineLength();

	APath* ptr = CurrentPath; this->TotalDistance = 0.0f;
	while (ptr) { TotalDistance += ptr->GetSplineComponent()->GetSplineLength(); ptr = ptr->GetNextPath(); }

	DynamicMaterial = Cast<UMaterialInstanceDynamic>(SpriteComponent->CreateAndSetMaterialInstanceDynamic(0));
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
			if (!CurrentPath) { Die(); return; }
			CurrentPathLength = CurrentPath->GetSplineComponent()->GetSplineLength();
		}

		SetActorLocation(CurrentPath->GetSplineComponent()->GetLocationAtDistanceAlongSpline(CurrentPathDistance, ESplineCoordinateSpace::World));
		SetActorRotation(CurrentPath->GetSplineComponent()->GetRotationAtDistanceAlongSpline(CurrentPathDistance, ESplineCoordinateSpace::World));
	}
	else { Die(); }
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0.0f) { Die(); }
	return DamageAmount;
}

void AEnemy::Die()
{
	for (AProjectile* Projectile : Projectiles) { Projectile->Destroy(); }
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
/// AEnemy - Public Methods
//////////////////////////////////////////////////////////////////////////
void AEnemy::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage) { if (Resistances.Contains(TypeOfDamage)) { return; } }
	TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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
	MoveAlongPath(DeltaTime);
}