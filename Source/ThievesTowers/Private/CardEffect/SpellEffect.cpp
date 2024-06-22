#include "CardEffect/SpellEffect.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Engine/DamageEvents.h"

ASpellEffect::ASpellEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetMobility(EComponentMobility::Movable);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sphere"));
	Capsule->SetupAttachment(Root);
	Capsule->SetCapsuleSize(100.0f, 100.0f);
	Capsule->SetCollisionProfileName("OverlapAllDynamic");
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ASpellEffect::OnOverlapBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &ASpellEffect::OnOverlapEnd);
	Capsule->SetMobility(EComponentMobility::Movable);
}

void ASpellEffect::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemy* Enemy = Cast<AEnemy>(OtherActor)) { OverlappingEnemies.Add(Enemy); }
}

void ASpellEffect::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemy* Enemy = Cast<AEnemy>(OtherActor)) { OverlappingEnemies.Remove(Enemy); }
}

void ASpellEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCanApplyEffect = false;

	FVector WorldPosition;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), UWidgetLayoutLibrary::GetMousePositionOnViewport(this) * UWidgetLayoutLibrary::GetViewportScale(this), WorldPosition, WorldDirection);

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(), WorldPosition, WorldPosition + WorldDirection * 10000.0f, ETraceTypeQuery::TraceTypeQuery1, false, { this }, EDrawDebugTrace::None, HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
	if (HitResults.Num() > 0)
	{
		for (FHitResult HitResult : HitResults)
		{
			SetActorLocation(HitResult.ImpactPoint);
			if (HitResult.GetActor()->ActorHasTag("Floor"))
			{
				bCanApplyEffect = true; return;
			}
		}
	}
	this->SetActorLocation(WorldPosition + WorldDirection * 1000.0f);
}

bool ASpellEffect::ApplyEffect()
{
	const TArray<AEnemy*> Enemies = OverlappingEnemies;
	
	if (bCanApplyEffect)
	{
		// TODO: Add particle system
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ASpellEffect::ApplyEffect() called"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemies hit: " + FString::FromInt(Enemies.Num())));
		for (AEnemy* Enemy : Enemies)
		{
			Enemy->TakeDamage(Damage, TypesOfDamage, FDamageEvent(), GetInstigatorController(), this);
		}
		Destroy(); return true;
	}
	return false;
}