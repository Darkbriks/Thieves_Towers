#include "Projectile.h"
#include "Enemy.h"
#include "GA_ThievesTowers.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/DamageEvents.h"
#include "ProjectileEffect/ProjectileEffect.h"

//////////////////////////////////////////////////////////////////////////
/// AProjectile - Constructor
//////////////////////////////////////////////////////////////////////////
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SceneComponent->Mobility = EComponentMobility::Movable;
	RootComponent = SceneComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->CastShadow = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	ArrowComponent->SetupAttachment(RootComponent);
}

//////////////////////////////////////////////////////////////////////////
/// AProjectile - Protected Methods
//////////////////////////////////////////////////////////////////////////
void AProjectile::MoveTowardsTarget(float DeltaTime)
{
	if (bLockOnTarget && TargetEnemy == nullptr) { Destroy(); return; }

	// Move towards target enemy
	FVector Direction = bLockOnTarget ? TargetEnemy->GetActorLocation() + (TargetEnemy->GetActorUpVector() * TargetEnemy->GetTargetZOffset()) - GetActorLocation() : TargetPosition - InitialPosition;
	Direction.Normalize(); const FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;

	//if (FVector::Dist(NewLocation, TargetEnemy->GetActorLocation()) < Epsilon)
	if ((bLockOnTarget && FVector::Dist(NewLocation, TargetEnemy->GetActorLocation() + (TargetEnemy->GetActorUpVector() * TargetEnemy->GetTargetZOffset())) < Epsilon) || (!bLockOnTarget && FVector::Dist(NewLocation, TargetPosition) < Epsilon)) { Impact(); return; }
	
	SetActorLocation(NewLocation);
	SetActorRotation(GetLookAtRotation(GetActorLocation(), bLockOnTarget ? TargetEnemy->GetActorLocation() + (TargetEnemy->GetActorUpVector() * TargetEnemy->GetTargetZOffset()) : TargetPosition));
}

void AProjectile::Impact()
{
	if (!TargetEnemy) { return; }
	TargetEnemy->TakeDamage(Damage, TypesOfDamage, FDamageEvent(), nullptr, this);
	for (TSubclassOf<UProjectileEffect> Effect : Effects)
	{
		//if (UProjectileEffect* NewEffect = NewObject<UProjectileEffect>(this, Effect)) { NewEffect->ApplyEffect(this->GetTransform(), TargetEnemy); }
		if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
		{
			GameInstance->GetProjectileEffect(Effect)->ApplyEffect(this->GetTransform(), TargetEnemy);
		}
	}
	Destroy();
}

FRotator const AProjectile::GetLookAtRotation(FVector Start, FVector Target)
{
	FVector Direction = Target - Start;
	Direction.Normalize();
	return FRotationMatrix::MakeFromX(Direction).Rotator();
}

//////////////////////////////////////////////////////////////////////////
/// AProjectile - Public Methods
//////////////////////////////////////////////////////////////////////////
void AProjectile::InitializeProjectile(FVector NewTargetPosition, AEnemy* NewTargetEnemy)
{
	if (bIsInitialized) { return; } bIsInitialized = true;
	InitialPosition = GetActorLocation();
	TargetPosition = NewTargetPosition;
	TargetEnemy = NewTargetEnemy;
	if (SpriteComponent->GetSprite() != nullptr) { SpriteComponent->SetVisibility(false); }
}

void AProjectile::Launch()
{
	if (bIsLaunched) { return; } bIsLaunched = true;
	if (!TargetEnemy) { Destroy(); return; }
	SetActorRotation(GetLookAtRotation(GetActorLocation(), bLockOnTarget ? TargetEnemy->GetActorLocation() : TargetPosition));
	if (SpriteComponent->GetSprite() != nullptr) { SpriteComponent->SetVisibility(true); }
}

//////////////////////////////////////////////////////////////////////////
/// AProjectile - Public Overrides Methods - Actor
//////////////////////////////////////////////////////////////////////////
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLockOnTarget && TargetEnemy == nullptr) { Destroy(); return; }
	if (bIsLaunched) { MoveTowardsTarget(DeltaTime); }
}

