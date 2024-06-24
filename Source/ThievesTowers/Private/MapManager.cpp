#include "MapManager.h"
#include "Struct/CardInfo.h"
#include "GA_ThievesTowers.h"
#include "WaveGenerator.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "CardEffect/CardEffect.h"
#include "CardHand/CardHandWidget.h"

AMapManager::AMapManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance())) { GameInstance->SetMapManager(this); }
	else { UE_LOG(LogTemp, Warning, TEXT("GameInstance not found")); }

	CardDeck.Empty();
	CardDiscard.Empty();
	Hand.Empty();

	// Recuperer le widget de la main
}

FCardInfo AMapManager::GetRandomCard()
{
	if (CardDataTable == nullptr) { return FCardInfo(); }
	TArray<FName> RowNames = CardDataTable->GetRowNames();
	if (RowNames.Num() == 0) { return FCardInfo(); }
	FName RandomRowName = RowNames[FMath::RandRange(0, RowNames.Num() - 1)];
	FCardInfo* CardInfo = CardDataTable->FindRow<FCardInfo>(RandomRowName, "");
	return CardInfo == nullptr ? FCardInfo() : *CardInfo;
}

void AMapManager::AddCardToHand(FCardInfo Card)
{
	if (Hand.Num() >= MaxHandSize) { return; } Hand.Add(Card);
	OnAddCardToHand.Broadcast(Card);
}

void AMapManager::RemoveCardFromHand(int CardIndex)
{
	if (CardIndex < 0 || CardIndex >= Hand.Num()) { return; }
	CardDiscard.Add(Hand[CardIndex]); Hand.RemoveAt(CardIndex);
	OnRemoveCardFromHand.Broadcast(CardIndex);

	if (Hand.Num() == 0) { PopulateHand(); }
}

void AMapManager::AddCardToDeck(FCardInfo Card)
{
	CardDeck.Add(Card);
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
	for (int i = 0; i < CardDeck.Num(); i++) { int RandomIndex = FMath::RandRange(0, CardDeck.Num() - 1); FCardInfo Temp = CardDeck[i]; CardDeck[i] = CardDeck[RandomIndex]; CardDeck[RandomIndex] = Temp; }
}

void AMapManager::CardPlayed(int CardIndex, ACardEffect* CardEffect)
{
	if (CardIndex < 0 || CardIndex >= Hand.Num()) { CardEffect->CancelEffect(); return; }
	FCardInfo Card = Hand[CardIndex];

	if (Mana < Card.GetManaCost() || Gold < Card.GetGoldCost()) { CardEffect->CancelEffect(); return; }
	if (!CardEffect->ApplyEffect()) { return; }
	RemoveCardFromHand(CardIndex);
	Mana -= Card.GetManaCost();
	Gold -= Card.GetGoldCost();
}

void AMapManager::BindCardHandWidgetDelegate(UCardHandWidget* CardHandWidget)
{
	CardHandWidget->OnCardPlayed.AddDynamic(this, &AMapManager::CardPlayed);
}

void AMapManager::InitMap()
{
	HeroName = "Hero";
	Mana = StartingMana;
	Gold = StartingGold;
	Life = StartingLife;

	for (int i = 0; i < DeckSize; i++) { AddCardToDeck(GetRandomCard()); }
	PopulateHand();
	//for (int i = 0; i < MaxHandSize; i++) { AddCardToHand(CardDeck[0]); RemoveCardFromDeck(0); }
	//if (FMath::RandBool()) { CardDiscard.Add(Hand[0]); RemoveCardFromHand(0); AddCardToHand(CardDeck[0]); CardDeck.RemoveAt(0); }

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
