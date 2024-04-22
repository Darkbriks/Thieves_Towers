#pragma once

#include "CoreMinimal.h"
#include "WaveParams.generated.h"

class AEnemy;

USTRUCT(BlueprintType)
struct FWaveParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AEnemy> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int EnemyCount;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpawnRate;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TimeBeforeFirstSpawn;
};