#include "DamageArea.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"

#include "Kismet/KismetSystemLibrary.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
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
		TArray<AActor*> OverlappingActors;
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
		TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		if (bUseBoxCollision) { UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation(), BoxExtent, TraceObjectTypes, AEnemy::StaticClass(), TArray<AActor*>(), OverlappingActors); }
		else { UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), SphereRadius, TraceObjectTypes, AEnemy::StaticClass(), TArray<AActor*>(), OverlappingActors); }
		
		for (AActor* Actor : OverlappingActors)
		{
			if (AEnemy* Enemy = Cast<AEnemy>(Actor))
			{
				Enemy->TakeDamage(Damage, DamageTypes, FDamageEvent(), nullptr, this);
				if (bApplyColorEffect) { Enemy->AddColorEffect(ColorEffect, ColorEffectDuration, ColorEffectAlpha); }
			}
		}
		DamageCooldown = DamageInterval;
	}
	else
	{
		DamageCooldown -= DeltaTime;
	}
}