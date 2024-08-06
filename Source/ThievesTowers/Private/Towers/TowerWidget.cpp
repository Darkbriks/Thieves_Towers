#include "Towers/TowerWidget.h"
#include "Towers/Tower.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTowerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PreviousTargetingModeButton->OnClicked.AddDynamic(this, &UTowerWidget::OnPreviousTargetingModeButtonClicked);
	NextTargetingModeButton->OnClicked.AddDynamic(this, &UTowerWidget::OnNextTargetingModeButtonClicked);
}

void UTowerWidget::SetTower(APrimitiveTower* InTower)
{
	Tower = Cast<ATower>(InTower);
	if (Tower)
	{
		TargetingModes = Tower->GetTargetingModes();
		CurrentTargetingModeIndex = 0;
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));

		if (TargetingModes.Num() > 1)
		{
			PreviousTargetingModeButton->SetVisibility(ESlateVisibility::Visible);
			NextTargetingModeButton->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			PreviousTargetingModeButton->SetVisibility(ESlateVisibility::Hidden);
			NextTargetingModeButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTowerWidget::OnPreviousTargetingModeButtonClicked()
{
	if (Tower && TargetingModes.Num() > 0)
	{
		CurrentTargetingModeIndex = (CurrentTargetingModeIndex - 1 + TargetingModes.Num()) % TargetingModes.Num();
		Tower->SetTargetingMode(TargetingModes[CurrentTargetingModeIndex]);
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));
	}
}

void UTowerWidget::OnNextTargetingModeButtonClicked()
{
	if (Tower && TargetingModes.Num() > 0)
	{
		CurrentTargetingModeIndex = (CurrentTargetingModeIndex + 1) % TargetingModes.Num();
		Tower->SetTargetingMode(TargetingModes[CurrentTargetingModeIndex]);
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));
	}
}