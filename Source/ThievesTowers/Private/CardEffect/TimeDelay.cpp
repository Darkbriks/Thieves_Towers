#include "CardEffect/TimeDelay.h"
#include "GA_ThievesTowers.h"

bool ATimeDelay::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			MapManager->AddBonusGold(BonusGold);
			MapManager->AddBonusMana(BonusMana);
			Destroy(); return true;
		}
	}
	return false;
}
