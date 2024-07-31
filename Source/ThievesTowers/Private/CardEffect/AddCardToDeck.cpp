#include "CardEffect/AddCardToDeck.h"
#include "GA_ThievesTowers.h"

bool AAddCardToDeck::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			MapManager->AddCardToDeck(GeneratedCard, CardGenerationAmount, InsertionType, bShuffleDeck);
			Destroy();
			return true;
		}
	}
	return false;
}