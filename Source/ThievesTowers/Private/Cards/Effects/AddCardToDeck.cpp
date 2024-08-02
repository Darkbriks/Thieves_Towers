#include "Cards/Effects/AddCardToDeck.h"
#include "Manager/GA_ThievesTowers.h"

bool AAddCardToDeck::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			if (!bPlaceInHand) { MapManager->AddCardToDeck(GeneratedCard, CardGenerationAmount, InsertionType, bShuffleDeck); }
			else { MapManager->AddCardToHand(GeneratedCard, CardGenerationAmount, InsertionType); }
			Destroy();
			return true;
		}
	}
	return false;
}