#include "ProjectileEffect/LightningEffect.h"
#include "Enemy/Enemy.h"
#include "Enum/TypeOfDamage.h"
#include "EngineUtils.h"

void ULightningEffect::InitializeEffect()
{
	CurrentTargets = 0;
	LightningTime = 0.0f;
	Enemies.Empty();
	bIsFinished = true;
}

void ULightningEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy)
{
	InitializeEffect();
	
	for (TActorIterator<AEnemy> ActorItr(TargetEnemy->GetWorld()); ActorItr; ++ActorItr)
	{
		if (FVector::Dist(ActorItr->GetActorLocation(), TargetEnemy->GetActorLocation()) <= Range && ActorItr->GetUniqueID() != TargetEnemy->GetUniqueID())
		{
			Enemies.Add(*ActorItr);
		}
	}

	if (IsValid(TargetEnemy)) { TargetEnemy->Freeze(FreezeTime, LightningColor, Damage, TypeOfDamage); }
	bIsFinished = false;
}

void ULightningEffect::Tick(float DeltaTime)
{
	if (bIsFinished) { return; }
	LightningTime += DeltaTime;

	if (LightningTime >= TimeBetweenTargets && CurrentTargets < NumberOfTargets && CurrentTargets < Enemies.Num())
	{
		LightningTime = 0.0f; CurrentTargets++;
		if (!IsValid(Enemies[CurrentTargets])) { return; }
		Enemies[CurrentTargets]->Freeze(FreezeTime, LightningColor, Damage, TypeOfDamage);
		if (CurrentTargets >= NumberOfTargets || CurrentTargets >= Enemies.Num()) { bIsFinished = true; }
	}
}