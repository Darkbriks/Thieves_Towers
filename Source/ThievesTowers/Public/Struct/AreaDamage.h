#pragma once

#include "CoreMinimal.h"
#include "AreaDamage.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAreaDamage
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AreaDamage - Attributes")
    float Radius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AreaDamage - Attributes")
    int Damage = 1;
};