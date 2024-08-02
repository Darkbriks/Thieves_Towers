#include "Manager/GA_ThievesTowers.h"
#include "Manager/MapManager.h"
#include "Cards/Card.h"
#include "Cards/Deck.h"
#include "Cards/CardInfo.h"
#include "Cards/CardType.h"
#include "Cards/Effects/CardEffect.h"
#include "Cards/Hand/CardHandWidget.h"
#include "WaveGenerator.h"
#include "Engine/World.h"
#include "EngineUtils.h"

AMapManager::AMapManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PostProcessVolume = nullptr;
}

void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance->SetMapManager(this); }
	else { UE_LOG(LogTemp, Warning, TEXT("GameInstance not found")); }

	CardDeck.Empty();
	CardDiscard.Empty();
	Hand.Empty();
}

void AMapManager::AddCardToHand(FCardInfo Card)
{
	if (Hand.Num() >= MaxHandSize) { return; } Hand.Add(Card);
	OnAddCardToHand.Broadcast(Card);
}

void AMapManager::RemoveCardFromHand(int CardIndex)
{
	if (CardIndex < 0 || CardIndex >= Hand.Num()) { return; }
	if (!Hand[CardIndex].GetIsDestroyedAfterUse()) { CardDiscard.Add(Hand[CardIndex]); }
	Hand.RemoveAt(CardIndex);
	OnRemoveCardFromHand.Broadcast(CardIndex);

	if (Hand.Num() == 0) { PopulateHand(); }
}

void AMapManager::AddCardToDeck(FCardInfo Card, const int Position)
{
	if (Position >= 0 && Position < CardDeck.Num()) { CardDeck.Insert(Card, Position); }
	else { CardDeck.Add(Card); }
}

void AMapManager::RemoveCardFromDeck(int CardIndex)
{
	if (CardIndex < 0 || CardIndex >= CardDeck.Num()) { return; } CardDeck.RemoveAt(CardIndex);
	if (CardDeck.Num() == 0) { PopulateDeck(); }
}

void AMapManager::PopulateHand() { for (int i = Hand.Num(); i < MaxHandSize; i++) { AddCardToHand(CardDeck[0]); RemoveCardFromDeck(0); } }

void AMapManager::PopulateDeck()
{
	// On melange la defausse, et on la remet dans le deck
	for (FCardInfo Card : CardDiscard) { AddCardToDeck(Card); }
	CardDiscard.Empty();
	ShuffleDeck();
}

void AMapManager::CardPlayed(int CardIndex, TArray<ACardEffect*> CardEffects)
{
	if (CardIndex < 0 || CardIndex >= Hand.Num()) { for (ACardEffect* CardEffect : CardEffects) { CardEffect->CancelEffect(); } return; }
	FCardInfo Card = Hand[CardIndex];

	if (Mana < Card.GetManaCost() || Gold < Card.GetGoldCost()) { for (ACardEffect* CardEffect : CardEffects) { CardEffect->CancelEffect(); } return; }
	
	for (ACardEffect* CardEffect : CardEffects)
	{
		if ( !CardEffect->ApplyEffect(Card) )
		{
			CardEffect->Destroy();
			UE_LOG(LogTemp, Error, TEXT("MapManager::CardPlayed - CardEffect not applied"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CardEffect not applied")));
		}
	}
	
	RemoveCardFromHand(CardIndex);
	Mana -= Card.GetManaCost();
	Gold -= Card.GetGoldCost();
}

void AMapManager::BindCardHandWidgetDelegate(UCardHandWidget* CardHandWidget)
{
	CardHandWidget->OnCardPlayed.AddDynamic(this, &AMapManager::CardPlayed);
}

void AMapManager::AddCardToDeck(TSubclassOf<UCard> Card, int NumberOfCards, int InsertionType, bool bShuffle)
{
	for (int i = 0; i < NumberOfCards; i++) { AddCardToDeck(Card->GetDefaultObject<UCard>()->GetCardInfo(), InsertionType == 0 ? 0 : InsertionType == 1 ? -1 : rand() % CardDeck.Num()); }
	if (bShuffle) { ShuffleDeck(); }
}

void AMapManager::InitDeck()
{
	UDeck* PlayerDeckObject = PlayerDeck->GetDefaultObject<UDeck>();
	int CardNumber = PlayerDeckObject->GetDeckSize();

	for (int i = 0; i < CardNumber; i++) { CardDeck.Add(PlayerDeckObject->GetCard(i)->GetDefaultObject<UCard>()->GetCardInfo()); }

	ShuffleDeck();

	// On met une tour en premiere position
	for (int i = 0; i < CardNumber; i++)
	{
		if (CardDeck[0].GetCardType() == ECardType::TOWER)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Tower found at position %d"), i));
			break;
		}
		FCardInfo Temp = CardDeck[0];
		CardDeck.RemoveAt(0);
		CardDeck.Add(Temp);
	}
}

void AMapManager::ShuffleDeck()
{
	for (int i = 0; i < CardDeck.Num(); i++)
	{
		int RandomIndex = FMath::RandRange(0, CardDeck.Num() - 1);
		FCardInfo Temp = CardDeck[i];
		CardDeck[i] = CardDeck[RandomIndex];
		CardDeck[RandomIndex] = Temp;
	}
}


void AMapManager::InitMap()
{
	HeroName = "Hero";
	Mana = StartingMana;
	Gold = StartingGold;
	Life = StartingLife;
	
	InitDeck();
	PopulateHand();
	InitRound(true);
}

void AMapManager::InitRound(bool bIsFirstRound)
{
	UE_LOG(LogTemp, Warning, TEXT("InitRound"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Round %d is initializing"), CurrentRound));

	PopulateHand();
	
	if (!bIsFirstRound)
	{
		Gold += ClearRoundGold + BonusGold;
		Mana = StartingMana + BonusMana;
		BonusGold = 0; BonusMana = 0;
	}

	CurrentRoundWaves.Empty();
	// Pour tous les objets de classe AWaveGenerator dans le monde
	for (TActorIterator<AWaveGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AWaveGenerator* WaveGenerator = *ActorItr;
		if (WaveGenerator->GetRoundNumber() == CurrentRound)
		{
			CurrentRoundWaves.Add(WaveGenerator);
		}
	}
}

void AMapManager::StartRound()
{
	UE_LOG(LogTemp, Warning, TEXT("StartRound"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Round %d is starting"), CurrentRound));

	for (AWaveGenerator* Wave : CurrentRoundWaves) { Wave->StartWaveGeneration(); }
}

void AMapManager::EndRound()
{
	UE_LOG(LogTemp, Warning, TEXT("EndRound"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Round %d is ending"), CurrentRound));
	CurrentRound++;

	if (CurrentRound >= RoundNames.Num()) { CurrentRound--; EndMap(); }
	else { InitRound(); }
}

void AMapManager::EndMap()
{
	UE_LOG(LogTemp, Warning, TEXT("EndMap"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Map is ending")));
}

void AMapManager::CheckEndRound()
{
	if (CurrentRoundWaves.Num() == 0) { EndRound(); }
}


void AMapManager::DrawCards(int NumberOfCards)
{
	for (int i = 0; i < NumberOfCards; i++)
	{
		if (Hand.Num() >= MaxHandSize + 1) { return; }
		if (CardDeck.Num() == 0) { PopulateDeck(); }
		Hand.Add(CardDeck[0]);
		OnAddCardToHand.Broadcast(CardDeck[0]);
		RemoveCardFromDeck(0);
	}
}