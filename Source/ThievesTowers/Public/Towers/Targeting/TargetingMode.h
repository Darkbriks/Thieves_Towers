#pragma once

#include "CoreMinimal.h"
#include "TargetingMode.generated.h"

class AEnemy;
class APrimitiveTower;

UCLASS()
class THIEVESTOWERS_API UTargetingMode : public UObject
{
	GENERATED_BODY()

public:
	virtual FName GetTargetingModeName() const { return NAME_None; }
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const { return nullptr; }
};
