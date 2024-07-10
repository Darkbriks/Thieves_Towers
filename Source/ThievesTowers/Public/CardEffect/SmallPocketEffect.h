#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "SmallPocketEffect.generated.h"

UCLASS()
class THIEVESTOWERS_API ASmallPocketEffect : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int NumberOfCards = 1;

public:
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
