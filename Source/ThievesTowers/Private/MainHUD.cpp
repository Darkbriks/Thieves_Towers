#include "MainHUD.h"
#include "Cards/Hand/CardHandWidget.h"
#include "Manager/GA_ThievesTowers.h"
#include "Manager/MapManager.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UMG.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		MapManager = GameInstance->GetMapManager();

		CardHand->OnDeckValidated.AddDynamic(this, &UMainHUD::OnDeckValidated);

		WaveButton->OnClicked.AddDynamic(this, &UMainHUD::OnWaveButtonClicked);
		PlayButton->OnClicked.AddDynamic(this, &UMainHUD::OnPlayButtonClicked);

		HeroNameField->SetText(FText::FromName(MapManager->GetHeroName()));
	}
}

void UMainHUD::OnDeckValidated()
{
	if (CardSelectionBackgroundFadeOut != nullptr) { PlayAnimation(CardSelectionBackgroundFadeOut); }
}

void UMainHUD::OnWaveButtonClicked()
{
	if (MapManager != nullptr) { MapManager->StartRound(); }
}

void UMainHUD::OnPlayButtonClicked()
{
	if (MapManager != nullptr)
	{
		MapManager->InitMap();
		PlayButton->RemoveFromParent();
		PlayButton = nullptr;
	}
}

FText UMainHUD::GetLifeText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetLife())); }
	return FText();
}

FText UMainHUD::GetGoldText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetGold())); }
	return FText();
}

FText UMainHUD::GetManaText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetMana())); }
	return FText();
}

FText UMainHUD::GetDrawText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetMaxHandSize())); }
	return FText();
}

FText UMainHUD::GetDiscardText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetMaxHandSize())); }
	return FText();
}