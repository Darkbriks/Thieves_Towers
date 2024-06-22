#include "CardEffect/SmallPocketEffect.h"
#include "GA_ThievesTowers.h"

bool ASmallPocketEffect::ApplyEffect()
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
