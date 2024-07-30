#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"
#include "FirstEnemyInRange.generated.h"

UCLASS()
class THIEVESTOWERS_API UFirstEnemyInRange : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange) const override
	{
		for (AEnemy* Enemy : EnemiesInRange) { if (Enemy->CanBeTargeted()) { return Enemy; } }
		return nullptr;
	}
};
