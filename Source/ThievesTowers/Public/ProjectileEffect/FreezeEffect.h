﻿#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Enemy.h"
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
    virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy) override { TargetEnemy->Freeze(FreezeTime, FreezeColor); }
};