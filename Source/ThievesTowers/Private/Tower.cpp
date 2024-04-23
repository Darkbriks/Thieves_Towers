#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
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
	CapsuleComponent->SetGenerateOverlapEvents(true);

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->CastShadow = true;
	FlipbookComponent->SetFlipbook(IdleAnimation);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Methods
//////////////////////////////////////////////////////////////////////////
bool ATower::Attack()
{
	if (EnemiesInRange.Num() > 0)
	{
		AEnemy* Enemy = EnemiesInRange[0];

		FVector ProjectileLocation = GetActorLocation();
		ProjectileLocation += GetActorForwardVector() * ProjectileXOffset;
		ProjectileLocation += GetActorRightVector() * ProjectileYOffset;
		ProjectileLocation += GetActorUpVector() * ProjectileZOffset;
		
		if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, FRotator::ZeroRotator))
		{
			Enemy->AddProjectile(Projectile);
			Projectile->InitializeProjectile(Enemy->GetActorLocation(), Enemy);
			Projectile->Launch();
			return true;
		}
	}
	return false;
}

void ATower::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Overlap"));
		EnemiesInRange.Add(Cast<AEnemy>(OtherActor));
	}
}

void ATower::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy End Overlap"));
		EnemiesInRange.Remove(Cast<AEnemy>(OtherActor));
		if (EnemiesInRange.Num() <= 0 && FlipbookComponent->GetFlipbook() == AttackAnimation) { FlipbookComponent->SetFlipbook(IdleAnimation); }
	}
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::BeginPlay()
{
	Super::BeginPlay();
	AttackAnimationTotalTime = AttackAnimation->GetTotalDuration();
	FlipbookComponent->SetFlipbook(IdleAnimation);
	CapsuleComponent->SetCapsuleRadius(AttackRange);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATower::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ATower::EndOverlap);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackCooldown += DeltaTime;
	if (AttackCooldown >= AttackSpeed) { if (Attack()) { AttackCooldown = 0.0f; } }

	if (EnemiesInRange.Num() > 0)
	{
		AEnemy* Enemy = EnemiesInRange[0];
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(Enemy->GetActorLocation() - GetActorLocation()).Rotator();
		SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));
	}

	if (FlipbookComponent->GetFlipbook() == AttackAnimation) { AttackAnimationCurrentTime += DeltaTime; }
	if (AttackAnimationCurrentTime >= AttackAnimationTotalTime) { AttackAnimationCurrentTime = 0.0f; FlipbookComponent->SetFlipbook(IdleAnimation); }

	// Si le temps avant la prochaine attaque est inférieur à ProjectileLaunchTime, on change l'animation
	if (AttackCooldown >= AttackSpeed - ProjectileLaunchTime && EnemiesInRange.Num() > 0 && FlipbookComponent->GetFlipbook() != AttackAnimation) { FlipbookComponent->SetFlipbook(AttackAnimation); }
}