#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"
#include "MostHealthy.generated.h"

UCLASS()
class THIEVESTOWERS_API UMostHealthy : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual FName GetTargetingModeName() const override { return "Most Healthy"; }
	
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const override
	{
		AEnemy* MostHealtlyEnemy = nullptr;
		
		for (AEnemy* Enemy : EnemiesInRange)
		{
			if (Enemy->CanBeTargeted() && (MostHealtlyEnemy == nullptr || Enemy->GetLife() > MostHealtlyEnemy->GetLife()))
			{
				MostHealtlyEnemy = Enemy;
			}
		}
		return MostHealtlyEnemy;
	}
};
