#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Enum/TypeOfDamage.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"
#include "CanonMortarEffect.generated.h"

class AEnemy;

UCLASS()
class THIEVESTOWERS_API UCanonMortarEffect : public UProjectileEffect
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	int MinLifeForAdditionalDamage = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	int AdditionalDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes = { ETypeOfDamage::Explosive };

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override
	{
		TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
		NewDamageTypes.Append(AdditionalTypesOfDamage);
	
		if (TargetEnemy)
		{
			int RealDamage = Damage + (TargetEnemy->GetLife() >= MinLifeForAdditionalDamage ? AdditionalDamage : 0);
			TargetEnemy->TakeDamage(RealDamage, NewDamageTypes, FDamageEvent(), nullptr, nullptr);
		}
	}
};
