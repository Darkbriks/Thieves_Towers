#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_BearerOfLittle.generated.h"

UCLASS()
class THIEVESTOWERS_API AEnemy_BearerOfLittle : public AEnemy
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	TSubclassOf<AEnemy> ClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int NumberOfEnemiesToSpawn = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float SpaceBetweenEnemies = 75.0f;

	void SpawnEnemies();

public:
	virtual void Die() override;
};
