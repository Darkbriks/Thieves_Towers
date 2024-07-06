#pragma once

#include "CoreMinimal.h"
#include "Enum/TypeOfDamage.h"
#include "ProjectileEffect.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class THIEVESTOWERS_API UProjectileEffect : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) {}
};
