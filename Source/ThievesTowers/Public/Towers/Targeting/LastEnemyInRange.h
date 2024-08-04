#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "LastEnemyInRange.generated.h"

UCLASS()
class THIEVESTOWERS_API ULastEnemyInRange : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual FName GetTargetingModeName() const override { return "Last"; }
	
	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const override
	{
		AEnemy* LastEnemy = nullptr;
		float MaxDistance = TNumericLimits<float>::Min();
		for (AEnemy* Enemy : EnemiesInRange)
		{
			const float Distance = Enemy->GetRemainingDistance();
			if (Enemy->CanBeTargeted() && Distance > MaxDistance)
			{
				MaxDistance = Distance;
				LastEnemy = Enemy;
			}
		}
		return LastEnemy;
	}
};
