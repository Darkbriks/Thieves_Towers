#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "Enemy/Enemy.h"
#include "FreezeEffect.generated.h"

UCLASS(Blueprintable)
class THIEVESTOWERS_API UFreezeEffect : public UProjectileEffect
{
    GENERATED_BODY()
    
protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Freeze Effect")
    float FreezeTime = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Freeze Effect")
    FColor FreezeColor = FColor(79, 143, 186, 255);
    
public:
    virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override { TargetEnemy->Freeze(FreezeTime, FreezeColor); }
};