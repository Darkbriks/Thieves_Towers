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
	virtual FName GetTargetingModeName() const override { return "First"; }
	
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const override
	{
		AEnemy* ClosestEnemy = nullptr;
		float MinDistance = TNumericLimits<float>::Max();
		for (AEnemy* Enemy : EnemiesInRange)
		{
			const float Distance = Enemy->GetRemainingDistance();
			if (Enemy->CanBeTargeted() &&Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestEnemy = Enemy;
			}
		}
		return ClosestEnemy;
	}
};
