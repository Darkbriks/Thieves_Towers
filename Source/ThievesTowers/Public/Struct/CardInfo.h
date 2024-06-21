#pragma once

#include "CoreMinimal.h"
#include "Enum/Rarity.h"
#include "Enum/CardType.h"
#include "CardInfo.generated.h"

class ACardEffect;

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
	TEnumAsByte<ECardType> CardType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int GoldCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TSubclassOf<ACardEffect> Effect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TArray<FName> Tags;

public:
	FCardInfo()
	{
		CardName = "Default Card";
		Description = FText::FromString("Default Description");
		CardTexture = nullptr;
		Rarity = ERarity::Common;
		CardType = ECardType::MISCELLANEOUS;
		ManaCost = 0;
		GoldCost = 0;
		Tags = TArray<FName>();
	}

	FCardInfo(FName NewCardName, FText NewDescription, UTexture2D* NewCardTexture, TEnumAsByte<ERarity> NewRarity, TEnumAsByte<ECardType> NewCardType, int NewManaCost, int NewGoldCost, TSubclassOf<ACardEffect> NewEffect, TArray<FName> NewTags)
	{
		CardName = NewCardName;
		Description = NewDescription;
		CardTexture = NewCardTexture;
		Rarity = NewRarity;
		CardType = NewCardType;
		ManaCost = NewManaCost;
		GoldCost = NewGoldCost;
		Effect = NewEffect;
		Tags = NewTags;
	}

	// Getters
	FName GetCardName() { return CardName; }
	FText GetDescription() { return Description; }
	UTexture2D* GetCardTexture() { return CardTexture; }
	TEnumAsByte<ERarity> GetRarity() { return Rarity; }
	TEnumAsByte<ECardType> GetCardType() { return CardType; }
	int GetManaCost() { return ManaCost; }
	int GetGoldCost() { return GoldCost; }
	TSubclassOf<ACardEffect> GetEffect() { return Effect; }
	TArray<FName> GetTags() { return Tags; }
};
