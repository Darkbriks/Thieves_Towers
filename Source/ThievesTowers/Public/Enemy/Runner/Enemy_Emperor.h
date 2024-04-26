#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Emperor.generated.h"

UCLASS()
class THIEVESTOWERS_API AEnemy_Emperor : public AEnemy
{
	GENERATED_BODY()

	TArray<AEnemy*> BuffedEnemies;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
    TSubclassOf<AEnemy> ClassToBuff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int MaxLifeBuff = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float Range = 500.0f;

	void Buff(AEnemy* Enemy);
	void Unbuff(AEnemy* Enemy);

public:
	virtual void Tick(float DeltaSeconds) override;
};
