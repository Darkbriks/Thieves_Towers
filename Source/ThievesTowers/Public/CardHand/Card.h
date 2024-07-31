#pragma once

#include "CoreMinimal.h"
#include "Struct/CardInfo.h"
#include "Card.generated.h"

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCard : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FCardInfo CardInfo;

public:
	UCard() { CardInfo = FCardInfo(); }

	FCardInfo GetCardInfo() const { return CardInfo; }
};