#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/CardInfo.h"
#include "Card.generated.h"

UCLASS(Blueprintable)
class THIEVESTOWERS_API ACard : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FCardInfo CardInfo;

public:
	ACard() { CardInfo = FCardInfo(); }
};