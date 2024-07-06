#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Enum/TypeOfDamage.h"
#include "LightningEffect.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class THIEVESTOWERS_API ULightningEffect : public UProjectileEffect
{
	GENERATED_BODY()
    
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float Range = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	int NumberOfTargets = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes = {ETypeOfDamage::Magical};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	FColor LightningColor = FColor(222, 158, 65, 255);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float FreezeTime = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lightning Effect")
	float TimeBetweenTargets = 0.2f;
    
public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override;
};