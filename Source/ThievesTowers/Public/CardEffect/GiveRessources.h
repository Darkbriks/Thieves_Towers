#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "GiveRessources.generated.h"

UCLASS()
class THIEVESTOWERS_API AGiveRessources : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int GoldAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int ManaAmount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int LifeAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true", Tooltip = "Bonus gold are given at the end of the round"))
	int BonusGold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true", Tooltip = "Bonus mana are given at the end of the round"))
	int BonusMana = 0;

public:
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
