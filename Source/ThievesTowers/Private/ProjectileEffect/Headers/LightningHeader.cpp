#include "ProjectileEffect/Headers/LightningHeader.h"
#include "Enemy/Enemy.h"
#include "Enum/TypeOfDamage.h"
#include "EngineUtils.h"
#include "GA_ThievesTowers.h"

ALightningHeader::ALightningHeader()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentTargets = 0;
	LightningTime = 0.0f;
}

void ALightningHeader::InitializeLightning(AEnemy* TargetEnemy, int NewNumberOfTargets, int NewDamage, float NewRange, TArray<TEnumAsByte<ETypeOfDamage>> NewTypeOfDamage, FColor NewLightningColor, float NewFreezeTime, float NewTimeBetweenTargets)
{
	this->NumberOfTargets = NewNumberOfTargets;
	this->Damage = NewDamage;
	this->Range = NewRange;
	this->TypeOfDamage = NewTypeOfDamage;
	this->LightningColor = NewLightningColor;
	this->FreezeTime = NewFreezeTime;
	this->TimeBetweenTargets = NewTimeBetweenTargets;

	if (UGA_ThievesTowers* ThievesTowersInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance = ThievesTowersInstance; }
	else { Destroy(); }
	
	if (TargetEnemy == nullptr) { Destroy(); return; }
	
	TargetEnemy->Freeze(FreezeTime, LightningColor, Damage, TypeOfDamage);
	Location = TargetEnemy->GetActorLocation();
	AffectedEnemies.Add(TargetEnemy);
}

void ALightningHeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LightningTime += DeltaTime;

	if (LightningTime >= TimeBetweenTargets)
	{
		LightningTime = 0.0f;
		CurrentTargets++;
		
		AEnemy* TargetEnemy = nullptr;
		for (AEnemy* Enemy : GameInstance->GetEnemies())
		{
			if (FVector::Dist(Enemy->GetActorLocation(), Location) <= Range && !AffectedEnemies.Contains(Enemy))
			{
				if (TargetEnemy == nullptr) { TargetEnemy = Enemy; }
				else if (FVector::Dist(Enemy->GetActorLocation(), Location) < FVector::Dist(TargetEnemy->GetActorLocation(), Location))
				{
					TargetEnemy = Enemy;
				}
			}
		}

		if (TargetEnemy == nullptr) { Destroy(); return; }
		
		TargetEnemy->Freeze(FreezeTime, LightningColor, Damage, TypeOfDamage);
		Location = TargetEnemy->GetActorLocation();
		AffectedEnemies.Add(TargetEnemy);
		
		if (CurrentTargets >= NumberOfTargets)
		{
			UE_LOG(LogTemp, Warning, TEXT("Destroying Lightning"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Destroying Lightning"));
			Destroy();
		}
	}
}