#pragma once

#include "CoreMinimal.h"
#include "TargetingMode.generated.h"

class AEnemy;

UCLASS()
class THIEVESTOWERS_API UTargetingMode : public UObject
{
	GENERATED_BODY()

public:
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange) const { return nullptr; }
};
