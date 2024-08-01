#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles/TypeOfDamage.h"
#include "LightningHelper.generated.h"

class UGA_ThievesTowers;
class AEnemy;

UCLASS()
class THIEVESTOWERS_API ALightningHelper : public AActor
{
	GENERATED_BODY()

	int CurrentTargets = 0;
	float LightningTime = 0.0f;
	FVector Location;
	TArray<AEnemy*> AffectedEnemies;

	int Damage;
	float Range;
	int NumberOfTargets;
	TArray<TEnumAsByte<ETypeOfDamage>> TypeOfDamage;
	FColor LightningColor;
	float FreezeTime;
	float TimeBetweenTargets;

	UPROPERTY()
	UGA_ThievesTowers* GameInstance;
	
public:	
	ALightningHelper();
	void InitializeLightning(AEnemy* TargetEnemy, int NewNumberOfTargets, int NewDamage, float NewRange, TArray<TEnumAsByte<ETypeOfDamage>> NewTypeOfDamage, FColor NewLightningColor, float NewFreezeTime, float NewTimeBetweenTargets);
	virtual void Tick(float DeltaTime) override;
};
