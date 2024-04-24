#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class THIEVESTOWERS_API UProjectileEffect : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	FName EffectName;
	
public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy) {}
};
