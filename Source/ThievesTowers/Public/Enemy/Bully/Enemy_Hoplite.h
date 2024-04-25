#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Hoplite.generated.h"

UCLASS()
class THIEVESTOWERS_API AEnemy_Hoplite : public AEnemy
{
	GENERATED_BODY()

	TArray<AEnemy_Hoplite*> HoplitesInRange;
	float InitialSpeed = 0.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
    int LifeGain = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float LooseSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float MinSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
    int Range = 250;

	virtual void InitializeEnemy(APath* NewPath, float NewCurrentDistance) override;

public:
	virtual void Tick(float DeltaTime) override;
};
