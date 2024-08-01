#pragma once

#include "CoreMinimal.h"
#include "Deck.generated.h"

class UCard;

UCLASS(Blueprintable)
class THIEVESTOWERS_API UDeck : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck - Attributes")
	FName DeckName = "DefaultDeck";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deck - Attributes")
	TArray<TSubclassOf<UCard>> Cards;

public:
	UDeck() {}

	FName GetDeckName() const { return DeckName; }
	TArray<TSubclassOf<UCard>> GetDeckCards() const { return Cards; }

	int GetDeckSize() const { return Cards.Num(); }
	TSubclassOf<UCard> GetCard(int Index) const { return Cards[Index]; }
};