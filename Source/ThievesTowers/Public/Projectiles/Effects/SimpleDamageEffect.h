#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"
#include "Projectiles/TypeOfDamage.h"
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
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes = { ETypeOfDamage::Physical };

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override
	{
		TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
		NewDamageTypes.Append(AdditionalTypesOfDamage);
	
		if (TargetEnemy)
		{
			TargetEnemy->TakeDamage(Damage, NewDamageTypes, FDamageEvent(), nullptr, nullptr);
		}
	}
};
