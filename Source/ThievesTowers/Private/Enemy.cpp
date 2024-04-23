#include "Enemy.h"

#include "Path.h"
#include "Projectile.h"
#include "Components/SplineComponent.h"
#include "PaperSpriteComponent.h"

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

//////////////////////////////////////////////////////////////////////////
///	AEnemy - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RemainingFreezeTime > 0.0f) { RemainingFreezeTime -= DeltaTime; return; }
	MoveAlongPath(DeltaTime);
}