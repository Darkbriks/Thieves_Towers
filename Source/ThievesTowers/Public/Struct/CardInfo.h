#pragma once

#include "CoreMinimal.h"
#include "Enum/Rarity.h"
#include "CardInfo.generated.h"

class UCardEffect;

USTRUCT(BlueprintType, Blueprintable)
struct FCardInfo : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FName CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	UTexture2D* CardTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TEnumAsByte<ERarity> Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int GoldCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TArray<TSubclassOf<UCardEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TArray<FName> Tags;

public:
	FCardInfo()
	{
		CardName = "Default Card";
		Description = FText::FromString("Default Description");
		CardTexture = nullptr;
		Rarity = ERarity::Common;
		ManaCost = 0;
		GoldCost = 0;
		Tags = TArray<FName>();
	}

	FCardInfo(FName NewCardName, FText NewDescription, UTexture2D* NewCardTexture, TEnumAsByte<ERarity> NewRarity, int NewManaCost, int NewGoldCost, TArray<TSubclassOf<UCardEffect>> NewEffects, TArray<FName> NewTags)
	{
		CardName = NewCardName;
		Description = NewDescription;
		CardTexture = NewCardTexture;
		Rarity = NewRarity;
		ManaCost = NewManaCost;
		GoldCost = NewGoldCost;
		Effects = NewEffects;
		Tags = NewTags;
	}

	// Getters
	FName GetCardName() { return CardName; }
	FText GetDescription() { return Description; }
	UTexture2D* GetCardTexture() { return CardTexture; }
	TEnumAsByte<ERarity> GetRarity() { return Rarity; }
	int GetManaCost() { return ManaCost; }
	int GetGoldCost() { return GoldCost; }
	TArray<TSubclassOf<UCardEffect>> GetEffects() { return Effects; }
	TArray<FName> GetTags() { return Tags; }
};
