#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "TimeDelay.generated.h"

UCLASS()
class THIEVESTOWERS_API ATimeDelay : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int BonusGold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int BonusMana = 0;

public:
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
