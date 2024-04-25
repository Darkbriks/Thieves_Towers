#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Druid.generated.h"

UCLASS()
class THIEVESTOWERS_API AEnemy_Druid : public AEnemy
{
	GENERATED_BODY()

	float HealCooldownTimer = 0.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int HealAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float HealCooldown = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float HealRange = 250.0f;

public:
	virtual void Tick(float DeltaTime) override;
};
