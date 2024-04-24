#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Enum/TypeOfDamage.h"
#include "LightningEffect.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class THIEVESTOWERS_API ULightningEffect : public UProjectileEffect, public FTickableGameObject
{
	GENERATED_BODY()

	int CurrentTargets = 0;
	float LightningTime = 0.0f;
	TArray<AEnemy*> Enemies;
	bool bIsFinished = true;
    
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float Range = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	int NumberOfTargets = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> TypeOfDamage = {ETypeOfDamage::Magical};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect") //de9e41
	FColor LightningColor = FColor(222, 158, 65, 255);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float FreezeTime = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float TimeBetweenTargets = 0.2f;

	void InitializeEffect();
    
public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy) override;

	void Tick(float DeltaTime) override;
	bool IsTickable() const override { return true; }
	TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULightningEffect, STATGROUP_Tickables); }
};