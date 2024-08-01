#include "Cards/Effects/DrawCard.h"
#include "Manager/GA_ThievesTowers.h"

bool ADrawCard::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			MapManager->DrawCards(NumberOfCards);
			Destroy();
			return true;
		}
	}
	return false;
}
