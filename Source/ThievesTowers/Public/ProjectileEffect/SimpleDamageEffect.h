#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Enum/TypeOfDamage.h"
#include "SimpleDamageEffect.generated.h"

class AEnemy;

UCLASS()
class THIEVESTOWERS_API USimpleDamageEffect : public UProjectileEffect
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes;

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override;
};
