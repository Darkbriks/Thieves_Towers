#pragma once

#include "CoreMinimal.h"
#include "CardEffect.h"
#include "DrawCard.generated.h"

UCLASS()
class THIEVESTOWERS_API ADrawCard : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int NumberOfCards = 1;

public:
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
