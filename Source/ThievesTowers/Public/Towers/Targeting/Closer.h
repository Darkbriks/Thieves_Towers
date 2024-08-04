#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"
#include "Towers/PrimitiveTower.h"
#include "Closer.generated.h"

UCLASS()
class THIEVESTOWERS_API UCloser : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual FName GetTargetingModeName() const override { return "Closer"; }

	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const override
	{
		AEnemy* ClosestEnemy = nullptr;
		float MinDistance = TNumericLimits<float>::Max();
		for (AEnemy* Enemy : EnemiesInRange)
		{
			const float Distance = FMath::Sqrt(FMath::Pow(Enemy->GetActorLocation().X - Tower->GetActorLocation().X, 2) + FMath::Pow(Enemy->GetActorLocation().Y - Tower->GetActorLocation().Y, 2));
			if (Enemy->CanBeTargeted() &&Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestEnemy = Enemy;
			}
		}
		return ClosestEnemy;
	}
};
