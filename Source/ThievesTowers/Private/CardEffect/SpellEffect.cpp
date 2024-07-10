#include "CardEffect/SpellEffect.h"
#include "GA_ThievesTowers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ProjectileEffect/ProjectileEffect.h"

ASpellEffect::ASpellEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetMobility(EComponentMobility::Movable);
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

bool ASpellEffect::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (bCanApplyEffect)
		{
			if (ParticleSystem != nullptr)
			{
				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ParticleSystem, GetActorLocation() + ParticleSystemTransform.GetLocation(), ParticleSystemTransform.GetRotation().Rotator(), ParticleSystemTransform.GetScale3D());
				if (NiagaraComponent != nullptr) { NiagaraComponent->Activate(); }
			}

			FVector Location = GetActorLocation();
			TSubclassOf<UProjectileEffect> SpellEffect = Effect;
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [GameInstance, SpellEffect, Location]()
			{
				UProjectileEffect* Effect = GameInstance->GetProjectileEffect(SpellEffect);
				if (Effect != nullptr) { Effect->ApplyEffect(FTransform(Location), nullptr, {}); }
			}, TimeBeforeDamage, false);
			Destroy();
			return true;
		}
	}
	Destroy();
	return false;
}