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
	PreviousTargetingModeButton->SetVisibility(ESlateVisibility::Hidden);
	NextTargetingModeButton->SetVisibility(ESlateVisibility::Hidden);
	CurrentTargetingModeName->SetVisibility(ESlateVisibility::Hidden);

	if (!InTower) { PrimitiveTower = nullptr; Tower = nullptr; return; }
	
	PrimitiveTower = InTower;
	TowerName->SetText(FText::FromString(PrimitiveTower->GetName()));
	
	Tower = Cast<ATower>(InTower);
	if (Tower)
	{
		TargetingModes = Tower->GetTargetingModes();
		CurrentTargetingModeIndex = TargetingModes.Find(Tower->GetCurrentTargetingMode());
		if (CurrentTargetingModeIndex == INDEX_NONE)
		{
			CurrentTargetingModeIndex = 0;
			Tower->SetTargetingMode(TargetingModes[CurrentTargetingModeIndex]);
		}
		
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));
		CurrentTargetingModeName->SetVisibility(ESlateVisibility::Visible);
		
		if (TargetingModes.Num() > 1)
		{
			PreviousTargetingModeButton->SetVisibility(ESlateVisibility::Visible);
			NextTargetingModeButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UTowerWidget::OnPreviousTargetingModeButtonClicked()
{
	if (Tower && TargetingModes.Num() > 1)
	{
		CurrentTargetingModeIndex = (CurrentTargetingModeIndex - 1 + TargetingModes.Num()) % TargetingModes.Num();
		Tower->SetTargetingMode(TargetingModes[CurrentTargetingModeIndex]);
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));
	}
}

void UTowerWidget::OnNextTargetingModeButtonClicked()
{
	if (Tower && TargetingModes.Num() > 1)
	{
		CurrentTargetingModeIndex = (CurrentTargetingModeIndex + 1) % TargetingModes.Num();
		Tower->SetTargetingMode(TargetingModes[CurrentTargetingModeIndex]);
		CurrentTargetingModeName->SetText(FText::FromString(TargetingModes[CurrentTargetingModeIndex]->GetName()));
	}
}