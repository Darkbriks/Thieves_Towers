#pragma once

#include "CoreMinimal.h"
#include "CardRarity.h"
#include "CardType.h"
#include "CardInfo.generated.h"

class APrimitiveTower;
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
	TArray<TSubclassOf<ACardEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes" , meta = (EditCondition = "CardType == ECardType::TOWER"))
	TSubclassOf<APrimitiveTower> Tower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	bool bIsDestroyedAfterUse;

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
		bIsDestroyedAfterUse = false;
		Tags = TArray<FName>();
	}

	FCardInfo(FName NewCardName, FText NewDescription, UTexture2D* NewCardTexture, TEnumAsByte<ERarity> NewRarity, TEnumAsByte<ECardType> NewCardType, int NewManaCost, int NewGoldCost, TArray<TSubclassOf<ACardEffect>> NewEffects, bool bNewIsDestroyedAfterUse, TArray<FName> NewTags)
	{
		CardName = NewCardName;
		Description = NewDescription;
		CardTexture = NewCardTexture;
		Rarity = NewRarity;
		CardType = NewCardType;
		ManaCost = NewManaCost;
		GoldCost = NewGoldCost;
		Effects = NewEffects;
		bIsDestroyedAfterUse = bNewIsDestroyedAfterUse;
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
	TArray<TSubclassOf<ACardEffect>> GetEffects() { return Effects; }
	TSubclassOf<APrimitiveTower> GetTower() { return Tower; }
	bool GetIsDestroyedAfterUse() { return bIsDestroyedAfterUse; }
	TArray<FName> GetTags() { return Tags; }
};
