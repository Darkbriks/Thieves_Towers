#include "Towers/PrimitiveTowerWidget.h"
#include "Towers/PrimitiveTower.h"
#include "Components/TextBlock.h"

void UPrimitiveTowerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPrimitiveTowerWidget::SetTower(APrimitiveTower* InTower)
{
	PrimitiveTower = InTower;
	TowerName->SetText(FText::FromString(PrimitiveTower->GetName()));
}