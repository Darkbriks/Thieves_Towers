#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"

//////////////////////////////////////////////////////////////////////////
/// ATower - Constructor
//////////////////////////////////////////////////////////////////////////
ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SceneComponent->Mobility = EComponentMobility::Movable;
	RootComponent = SceneComponent;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleSize(AttackRange, 5000.0f);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Methods
//////////////////////////////////////////////////////////////////////////
bool ATower::Attack()
{
	TArray<AActor*> OverlappingActors;
	CapsuleComponent->GetOverlappingActors(OverlappingActors, AEnemy::StaticClass());

	if (OverlappingActors.Num() > 0)
	{
		AEnemy* Enemy = Cast<AEnemy>(OverlappingActors[0]);
		if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), FRotator::ZeroRotator))
		{
			Enemy->AddProjectile(Projectile);
			Projectile->InitializeProjectile(Enemy->GetActorLocation(), Enemy);
			Projectile->Launch();
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->SetCapsuleRadius(AttackRange);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackCooldown -= DeltaTime;
	if (AttackCooldown <= 0.0f) { if (Attack()) { AttackCooldown = AttackSpeed; } }
}