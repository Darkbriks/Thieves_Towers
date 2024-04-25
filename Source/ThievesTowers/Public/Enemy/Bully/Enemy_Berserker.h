#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Berserker.generated.h"

class UPaperSprite;

UCLASS()
class THIEVESTOWERS_API AEnemy_Berserker : public AEnemy
{
	GENERATED_BODY()

	bool bCanEnterInBersekerMode = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float BerserkerSpeedGain = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int BerserkerLifeLoss = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	UPaperSprite* BerserkerSprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes", meta = (Tooltip = "Types of damage that will trigger the berserker mode"))
	TArray<TEnumAsByte<ETypeOfDamage>> BerserkerTypesOfDamage;

public:
	virtual void TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
