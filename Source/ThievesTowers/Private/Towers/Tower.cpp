#include "Towers/Tower.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/Enemy.h"
#include "Projectile.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////
/// ATower - Constructor
//////////////////////////////////////////////////////////////////////////
ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->SetFlipbook(IdleAnimation);
	FlipbookComponent->CastShadow = true;

	BasementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasementMesh"));
	BasementMesh->SetupAttachment(RootComponent);
	BasementMesh->SetGenerateOverlapEvents(false);

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATower::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ATower::EndOverlap);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Methods
//////////////////////////////////////////////////////////////////////////
AEnemy* ATower::GetEnemyInRange()
{
	if (TargetingMode == nullptr)
	{
		TargetingMode = NewObject<UTargetingMode>(this, TargetingModeClass);
	}
	return TargetingMode->GetEnemy(EnemiesInRange);
}

void ATower::Anim(float DeltaTime)
{
	if (AnimationCooldown > 0)
	{
		if (FlipbookComponent->GetFlipbook() != AttackAnimation) { FlipbookComponent->SetFlipbook(AttackAnimation); }
	}
	else if (AttackCooldown > AnimationOverflow)
	{
		if (FlipbookComponent->GetFlipbook() != IdleAnimation) { FlipbookComponent->SetFlipbook(IdleAnimation); }
	}

	if (AEnemy* Enemy = GetEnemyInRange())
	{
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(FlipbookComponent->GetComponentLocation(), Enemy->GetActorLocation());
		const FRotator CurrentRotation = FlipbookComponent->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed); NewRotation.Pitch = 0.0f;
		FlipbookComponent->SetWorldRotation(NewRotation);
	}
}

bool ATower::Attack()
{
	if (AEnemy* Enemy = GetEnemyInRange())
	{
		FVector ProjectileLocation = GetActorLocation();
		ProjectileLocation += GetActorForwardVector() * ProjectileXOffset;
		ProjectileLocation += GetActorRightVector() * ProjectileYOffset;
		ProjectileLocation += GetActorUpVector() * ProjectileZOffset;
		
		if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, FRotator::ZeroRotator))
		{
			Enemy->AddProjectile(Projectile);
			Projectile->InitializeProjectile(Enemy->GetActorLocation(), Enemy, AdditionalTypesOfDamage);
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
		EnemiesInRange.Add(Cast<AEnemy>(OtherActor));
	}
}

void ATower::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		EnemiesInRange.Remove(Cast<AEnemy>(OtherActor));
		if (GetEnemyInRange() != nullptr) { AnimationCooldown = 0.0f; }
	}
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::BeginPlay()
{
	Super::BeginPlay();
	AnimationOverflow = AttackAnimation->GetTotalDuration() - ProjectileLaunchTime;
	FlipbookComponent->SetFlipbook(IdleAnimation);

	Activate();
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActivated) { return; }
	
	if (AttackCooldown < AttackSpeed - ProjectileLaunchTime + DeltaTime) { AttackCooldown += DeltaTime; }
	else if (GetEnemyInRange() != nullptr)
	{
		if (AnimationCooldown < ProjectileLaunchTime + DeltaTime) { AnimationCooldown += DeltaTime; }
		else
		{
			Attack();
			AttackCooldown = 0.0f;
			AnimationCooldown = 0.0f;
		}
	}
	else { AnimationCooldown = 0.0f; }

	Anim(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Public Methods
//////////////////////////////////////////////////////////////////////////

void ATower::Deactivate()
{
	Super::Deactivate();
	AttackCooldown = 0.0f;
	AnimationCooldown = 0.0f;
	AnimationOverflow = 0.0f;
}