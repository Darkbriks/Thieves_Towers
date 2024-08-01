#pragma once

#include "CoreMinimal.h"
#include "Cards/CardInfo.h"
#include "CardHandInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCardHandInterface : public UInterface
{
	GENERATED_BODY()
};

class THIEVESTOWERS_API ICardHandInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddCardToHand(FCardInfo NewCard);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCardFromHand(int Index);
};