#include "Tower.h"
#include "GA_ThievesTowers.h"
#include "Enemy/Enemy.h"
#include "Projectile.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	BasementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasementMesh"));
	BasementMesh->SetupAttachment(RootComponent);
	BasementMesh->SetGenerateOverlapEvents(false);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName("OverlapAllDynamic");
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->ComponentTags.Add("Tower-Basement");
}

//////////////////////////////////////////////////////////////////////////
/// ATower - Protected Methods
//////////////////////////////////////////////////////////////////////////
int ATower::IndexOfFirstEnemyInRange()
{
	int Index = -1;
	for (int i = 0; i < EnemiesInRange.Num(); i++) { if (EnemiesInRange[i]->CanBeTargeted()) { Index = i; break; } }
	return Index;
}

AEnemy* ATower::GetFirstEnemyInRange()
{
	for (AEnemy* Enemy : EnemiesInRange) { if (Enemy->CanBeTargeted()) { return Enemy; } }
	return nullptr;
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

	if (AEnemy* Enemy = GetFirstEnemyInRange())
	{
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(FlipbookComponent->GetComponentLocation(), Enemy->GetActorLocation());
		const FRotator CurrentRotation = FlipbookComponent->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed); NewRotation.Pitch = 0.0f;
		FlipbookComponent->SetWorldRotation(NewRotation);
	}
}

bool ATower::Attack()
{
	if (AEnemy* Enemy = GetFirstEnemyInRange())
	{
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
	if (OtherActor->IsA(AEnemy::StaticClass())) { EnemiesInRange.Add(Cast<AEnemy>(OtherActor)); }
}

void ATower::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		EnemiesInRange.Remove(Cast<AEnemy>(OtherActor));
		if (IndexOfFirstEnemyInRange() != -1) { AnimationCooldown = 0.0f; }
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
	CapsuleComponent->SetCapsuleRadius(AttackRange);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATower::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ATower::EndOverlap);

	if (UGA_ThievesTowers *GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance->AddTower(this); }
	Activate();
}

void ATower::Destroyed()
{
	Super::Destroyed();
	if (UGA_ThievesTowers *GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance->RemoveTower(this); }
}


//////////////////////////////////////////////////////////////////////////
/// ATower - Public Overrides Methods - AActor
//////////////////////////////////////////////////////////////////////////
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActivated) { return; }
	
	if (AttackCooldown < AttackSpeed - ProjectileLaunchTime + DeltaTime) { AttackCooldown += DeltaTime; }
	else if (IndexOfFirstEnemyInRange() != -1)
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
void ATower::Activate()
{
	bIsActivated = true;
}

void ATower::Deactivate()
{
	bIsActivated = false;
	AttackCooldown = 0.0f;
	AnimationCooldown = 0.0f;
	AnimationOverflow = 0.0f;
}