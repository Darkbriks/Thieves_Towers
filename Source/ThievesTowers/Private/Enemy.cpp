#include "Enemy.h"

#include "Path.h"
//#include "Projectile.h" TODO
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
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

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::World);
	HealthBarWidget->SetDrawSize(FVector2D(100.0f, 10.0f));
	HealthBarWidget->SetVisibility(true);
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

void AEnemy::Die()
{
	//for (AProjectile* Projectile : Projectiles) { Projectile->Destroy(); } TODO
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
/// AEnemy - Public Methods
//////////////////////////////////////////////////////////////////////////
float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0.0f) { Die(); }
	return DamageAmount;
}

//////////////////////////////////////////////////////////////////////////
///	AEnemy - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAlongPath(DeltaTime);
}