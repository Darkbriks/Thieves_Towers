#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Assassin.generated.h"

class UPaperSprite;

UCLASS()
class THIEVESTOWERS_API AEnemy_Assassin : public AEnemy
{
	GENERATED_BODY()

	float CamouflageTimeRemaining = 0.0f;
	bool bCanCamouflage = true;
	bool bIsCamouflaged = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float CamouflageTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	UPaperSprite* AfterCamouflageSprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes", meta = (Tooltip = "Types of damage that will trigger the camouflage"))
	TArray<TEnumAsByte<ETypeOfDamage>> CamouflageTypesOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	FColor CamouflageColor = FColor(168, 181, 178, 255);

	void Camouflage();

public:
	virtual void TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
};
