#include "MainHUD.h"
#include "Cards/Hand/CardHandWidget.h"
#include "Manager/GA_ThievesTowers.h"
#include "Manager/MapManager.h"
#include "Towers/TowerWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		MapManager = GameInstance->GetMapManager();
		MapManager->SetMainHUD(this);

		CardHand->OnDeckValidated.AddDynamic(this, &UMainHUD::OnDeckValidated);

		WaveButton->OnClicked.AddDynamic(this, &UMainHUD::OnWaveButtonClicked);
		PlayButton->OnClicked.AddDynamic(this, &UMainHUD::OnPlayButtonClicked);

		HeroNameField->SetText(FText::FromName(MapManager->GetHeroName()));
	}

	TowerWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUD::OnDeckValidated()
{
	if (BackgroundFadeOut != nullptr) { PlayAnimation(BackgroundFadeOut); }
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
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetCardDeck().Num())); }
	return FText();
}

FText UMainHUD::GetDiscardText() const
{
	if (MapManager != nullptr) { return FText::FromString(FString::FromInt(MapManager->GetCardDiscard().Num())); }
	return FText();
}

void UMainHUD::TowerSelected(APrimitiveTower* InTower) const
{
	if (InTower == nullptr) { return; }
	TowerWidget->SetTower(InTower);
	TowerWidget->SetVisibility(ESlateVisibility::Visible);
}

void UMainHUD::TowerDeselected(APrimitiveTower* InTower) const
{
	if (InTower == TowerWidget->GetTower())
	{
		TowerWidget->SetTower(nullptr);
		TowerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}