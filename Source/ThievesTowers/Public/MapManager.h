#pragma once

#include "CoreMinimal.h"

#include "CardHand/CardHandWidget.h"

#include "Struct/CardInfo.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

class APostProcessVolume;
class AWaveGenerator;
class ACard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddCardToHand, FCardInfo, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemoveCardFromHand, int, CardIndex);

UCLASS()
class THIEVESTOWERS_API AMapManager : public AActor
{
	GENERATED_BODY()

	const int DeckSize = 8;
	const int MaxHandSize = 5;
	const int StartingMana = 3;
	const int StartingGold = 350;
	const int StartingLife = 100;
	const int ClearRoundGold = 200;

	int BonusGold = 0;
	int BonusMana = 0;

	TArray<AWaveGenerator*> CurrentRoundWaves;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	UDataTable* CardDataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	FName MapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	TArray<FName> RoundNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
    int CurrentRound = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	FName HeroName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	TArray<FCardInfo> Hand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	TArray<FCardInfo> CardDeck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	TArray<FCardInfo> CardDiscard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	int Mana = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	int Gold = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager - Round")
	int Life = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapManager")
	APostProcessVolume* PostProcessVolume;

	// Methods
	virtual void BeginPlay() override;

	FCardInfo GetRandomCard();
	void AddCardToHand(FCardInfo Card);
	void RemoveCardFromHand(int CardIndex);
	void AddCardToDeck(FCardInfo Card);
	void RemoveCardFromDeck(int CardIndex);
	void PopulateHand();
	void PopulateDeck();

	UFUNCTION()
	void CardPlayed(int CardIndex, ACardEffect* CardEffect);

public:
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FAddCardToHand OnAddCardToHand;

	UPROPERTY(BlueprintAssignable)
	FRemoveCardFromHand OnRemoveCardFromHand;

	void BindCardHandWidgetDelegate(UCardHandWidget* CardHandWidget);
	
	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetDeckSize() { return DeckSize; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMaxHandSize() { return MaxHandSize; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetMapName() { return MapName; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetRoundName() { return RoundNames[CurrentRound]; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetHeroName() { return HeroName; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FCardInfo> GetHand() { return Hand; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMana() { return Mana; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetGold() { return Gold; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetLife() { return Life; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetClearRoundGold() { return ClearRoundGold; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FCardInfo> GetCardDeck() { return CardDeck; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCardDeckSize() { return CardDeck.Num(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FCardInfo> GetCardDiscard() { return CardDiscard; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCardDiscardSize() { return CardDiscard.Num(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	APostProcessVolume* GetPostProcessVolume() { return PostProcessVolume; }

	// Setters
	void AddMana(int ManaAmount) { Mana += ManaAmount; }
	void AddGold(int GoldAmount) { Gold += GoldAmount; }
	void AddLife(int LifeAmount) { Life += LifeAmount; }
	void AddBonusGold(int BonusGoldAmount) { BonusGold += BonusGoldAmount; }
	void AddBonusMana(int BonusManaAmount) { BonusMana += BonusManaAmount; }
	
	void RemoveWave(AWaveGenerator* Wave) { CurrentRoundWaves.Remove(Wave); }

	// Methods
	UFUNCTION(BlueprintCallable)
	void InitMap();

	UFUNCTION(BlueprintCallable)
	void InitRound(bool bIsFirstRound = false);
	
	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintCallable)
	void EndRound();

	UFUNCTION(BlueprintCallable)
	void EndMap();

	UFUNCTION(BlueprintCallable)
	void CheckEndRound();

	UFUNCTION(BlueprintCallable)
	void DrawCards(int NumberOfCards = 1);

	AMapManager();
};
