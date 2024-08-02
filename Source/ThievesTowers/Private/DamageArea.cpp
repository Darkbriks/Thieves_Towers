#include "DamageArea.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Root);
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionProfileName("OverlapAll");
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamageArea::BeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADamageArea::EndOverlap);
}

void ADamageArea::BeginPlay()
{
	Super::BeginPlay();

	if (bCooldownBeforeFirstDamage) { DamageCooldown = DamageInterval; }
}

void ADamageArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CreationTime += DeltaTime;
	if (!bInfinitely && CreationTime >= Duration) { Destroy(); }
	if (DamageCooldown <= 0)
	{
		TArray<AEnemy*> Enemies = EnemiesInRange;
		for (AEnemy* Enemy : Enemies)
		{
			Enemy->TakeDamage(Damage, DamageTypes, FDamageEvent(), nullptr, this);
			if (bApplyColorEffect) { Enemy->AddColorEffect(ColorEffect, ColorEffectDuration, ColorEffectAlpha); }
		}
		DamageCooldown = DamageInterval;
	}
	else
	{
		DamageCooldown -= DeltaTime;
	}
}

void ADamageArea::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Enemy in range");
		EnemiesInRange.Add(Cast<AEnemy>(OtherActor));
	}
}

void ADamageArea::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		EnemiesInRange.Remove(Cast<AEnemy>(OtherActor));
	}
}