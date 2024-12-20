#include "Cards/Effects/GiveResources.h"
#include "Manager/GA_ThievesTowers.h"

bool AGiveResources::ApplyEffect(FCardInfo CardInfo)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			MapManager->AddGold(GoldAmount);
			MapManager->AddMana(ManaAmount);
			MapManager->AddLife(LifeAmount);
			MapManager->AddBonusGold(BonusGold);
			MapManager->AddBonusMana(BonusMana);
			Destroy();
			return true;
		}
	}
	return false;
}
