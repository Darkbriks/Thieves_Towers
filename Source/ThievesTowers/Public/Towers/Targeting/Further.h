#pragma once

#include "CoreMinimal.h"
#include "Towers/Targeting/TargetingMode.h"
#include "Enemy/Enemy.h"
#include "Towers/PrimitiveTower.h"
#include "Further.generated.h"

UCLASS()
class THIEVESTOWERS_API UFurther : public UTargetingMode
{
	GENERATED_BODY()

public:
	virtual FName GetTargetingModeName() const override { return "Further"; }

	virtual AEnemy* GetEnemy(TArray<AEnemy*> EnemiesInRange, APrimitiveTower* Tower) const override
	{
		AEnemy* FarthestEnemy = nullptr;
		float MaxDistance = TNumericLimits<float>::Min();
		for (AEnemy* Enemy : EnemiesInRange)
		{
			const float Distance = FMath::Sqrt(FMath::Pow(Enemy->GetActorLocation().X - Tower->GetActorLocation().X, 2) + FMath::Pow(Enemy->GetActorLocation().Y - Tower->GetActorLocation().Y, 2));
			if (Enemy->CanBeTargeted() &&Distance > MaxDistance)
			{
				MaxDistance = Distance;
				FarthestEnemy = Enemy;
			}
		}
		return FarthestEnemy;
	}
};
