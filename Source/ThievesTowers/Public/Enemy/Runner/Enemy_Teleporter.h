#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Enemy_Teleporter.generated.h"

class UPaperSprite;

UCLASS()
class THIEVESTOWERS_API AEnemy_Teleporter : public AEnemy
{
	GENERATED_BODY()

	bool bCanUseTeleport = true;
	bool bIsTeleporting = false;
	float StartDistance = 0.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float TeleportDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float SpeedMultiplier = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	UPaperSprite* AfterTeleportSprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes", meta = (Tooltip = "Types of damage that will trigger the teleport"))
	TArray<TEnumAsByte<ETypeOfDamage>> TeleportTypesOfDamage;
	
	void StartFakeTeleport();
	void EndFakeTeleport();

public:
	virtual void TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
};
