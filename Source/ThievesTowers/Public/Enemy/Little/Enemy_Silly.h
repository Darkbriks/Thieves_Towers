#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "GA_ThievesTowers.h"
#include "Enemy_Silly.generated.h"

UCLASS()
class THIEVESTOWERS_API AEnemy_Silly : public AEnemy
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int Range = 1000;
	
public:
	int GetRange() const { return Range; }
};
