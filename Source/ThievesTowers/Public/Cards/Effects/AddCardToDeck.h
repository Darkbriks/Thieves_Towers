#pragma once

#include "CoreMinimal.h"
#include "CardEffect.h"
#include "AddCardToDeck.generated.h"

class UCard;

UENUM(Blueprintable)
enum EInsertionType
{
	BEGIN = 0,
	END = 1,
	RANDOM = 2
};

UCLASS()
class THIEVESTOWERS_API AAddCardToDeck : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCard> GeneratedCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int CardGenerationAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EInsertionType> InsertionType = EInsertionType::RANDOM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	bool bShuffleDeck = false;

public:
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
