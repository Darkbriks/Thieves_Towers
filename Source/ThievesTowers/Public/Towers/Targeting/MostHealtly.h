#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"
#include "MostHealtly.generated.h"

UCLASS()
class THIEVESTOWERS_API UMostHealtly : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange) const override
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
