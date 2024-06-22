#include "CardHand/CardHandWidget.h"
#include "CardHand/CardWidget.h"
#include "CardEffect/CardEffect.h"
#include "GA_ThievesTowers.h"
#include "Components/Overlay.h"

void UCardHandWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		AMapManager* MapManager = GameInstance->GetMapManager();
		if (MapManager != nullptr)
		{
			MapManager->OnAddCardToHand.AddDynamic(this, &UCardHandWidget::AddCard);
			MapManager->OnRemoveCardFromHand.AddDynamic(this, &UCardHandWidget::RemoveCard);
			MapManager->BindCardHandWidgetDelegate(this);
		}
	}
}

FCardInfo UCardHandWidget::GetRandomCard()
{
	if (CardDataTable == nullptr) { return FCardInfo(); }
	TArray<FName> RowNames = CardDataTable->GetRowNames();
	if (RowNames.Num() == 0) { return FCardInfo(); }
	FName RandomRowName = RowNames[FMath::RandRange(0, RowNames.Num() - 1)];
	FCardInfo* CardInfo = CardDataTable->FindRow<FCardInfo>(RandomRowName, "");
	return CardInfo == nullptr ? FCardInfo() : *CardInfo;
}

int UCardHandWidget::GetIndexFromCenter(int Index)
{
	if (CardHandOverlay == nullptr) { return 0; }
	if (CardWidgets.Num() == 1) { return 0; }
	return FMath::Lerp(-(CardWidgets.Num() - 1), CardWidgets.Num() - 1, Index / static_cast<float>(CardWidgets.Num() - 1));
}

FVector2D UCardHandWidget::GetCenterPosition()
{
	if (CardHandOverlay == nullptr) { return FVector2D(); }
	return CardHandOverlay->GetCachedGeometry().GetLocalSize() / 2.0f;
}

float UCardHandWidget::GetCardXPosition(int Index)
{
	if (CardHandOverlay == nullptr) { return 0.0f; }
	return GetCenterPosition().X + XArcRadius * FMath::Sin(FMath::DegreesToRadians(GetCardAngle(Index))) - CardWidgets[Index]->GetCardSize().X / 2.0f;
}

float UCardHandWidget::GetCardYPosition(int Index)
{
	if (CardHandOverlay == nullptr) { return 0.0f; }
	return GetCenterPosition().Y - YArcRadius * FMath::Cos(FMath::DegreesToRadians(GetCardAngle(Index))) - CardWidgets[Index]->GetCardSize().Y / 2.0f - ZOffset;
}

float UCardHandWidget::GetCardAngle(int Index) { return GetIndexFromCenter(Index) * CardAngle; }

void UCardHandWidget::UpdateCardPositions()
{
	if (CardHandOverlay == nullptr) { return; }
	for (int i = 0; i < CardWidgets.Num(); i++)
	{
		FWidgetTransform NewTransform;
		NewTransform.Angle = GetCardAngle(i);
		NewTransform.Translation = FVector2D(GetCardXPosition(i), GetCardYPosition(i));
		if (HoveredCardIndex == i) { NewTransform.Translation.Y += CardWidgets[i]->GetHoverOffset().Y; NewTransform.Angle = 0.0f; }
		if (HoveredCardIndex != -1 && HoveredCardIndex < i) { NewTransform.Translation.X += CardWidgets[i]->GetHoverOffset().X; }
		NewTransform.Scale = HoveredCardIndex == i ? FVector2D(CardWidgets[i]->GetHoverScale(), CardWidgets[i]->GetHoverScale()) : FVector2D(CardWidgets[i]->GetUnhoverScale(), CardWidgets[i]->GetUnhoverScale());

		CardWidgets[i]->StartMoving(NewTransform);
	}
}

void UCardHandWidget::OnCardHovered(UCardWidget* HoveredCard)
{
	if (CardHandOverlay == nullptr) { return; }
	HoveredCardIndex = CardWidgets.Find(HoveredCard);
	UpdateCardPositions();
}

void UCardHandWidget::OnCardUnhovered(UCardWidget* UnhoveredCard)
{
	if (CardHandOverlay == nullptr) { return; }
	if (HoveredCardIndex == CardWidgets.Find(UnhoveredCard)) { HoveredCardIndex = -1; UpdateCardPositions(); }
}

void UCardHandWidget::OnCardDragged(UCardWidget* DraggedCard)
{
	if (CardHandOverlay == nullptr) { return; }
	this->DraggedCardReferance = DraggedCard;

	FCardInfo CardInfo = DraggedCard->GetCardInfo();
	CardEffect = GetWorld()->SpawnActor<ACardEffect>(CardInfo.GetEffect());
}

void UCardHandWidget::OnCardDragCancelled(UCardWidget* CancelDraggedCard, bool bDragIsCancelled)
{
	if (CardHandOverlay == nullptr || bDragIsCancelled) { CardEffect->CancelEffect(); return; }
	if (DraggedCardReferance == CancelDraggedCard) { DraggedCardReferance = nullptr; }
	OnCardPlayed.Broadcast(CardWidgets.Find(CancelDraggedCard), CardEffect);
}

void UCardHandWidget::OnCardDragEnter(UCardWidget* HoveredCard)
{
	if (CardHandOverlay == nullptr) { return; }
	DragHoveredCard = HoveredCard;
}

void UCardHandWidget::OnCardDragLeave(UCardWidget* UnhoveredCard)
{
	if (CardHandOverlay == nullptr) { return; }
	if (DragHoveredCard == UnhoveredCard) { DragHoveredCard = nullptr; }
}

void UCardHandWidget::AddCard(FCardInfo Card)
{
	if (CardHandOverlay == nullptr) { return; }
	
	UCardWidget* NewCard = CreateWidget<UCardWidget>(this, CardWidgetClass);
	NewCard->SetCardInfo(Card);
	CardHandOverlay->AddChild(NewCard);
	CardWidgets.Add(NewCard);
	
	NewCard->OnHoverCard.AddDynamic(this, &UCardHandWidget::OnCardHovered);
	NewCard->OnUnhoverCard.AddDynamic(this, &UCardHandWidget::OnCardUnhovered);
	NewCard->OnDragCard.AddDynamic(this, &UCardHandWidget::OnCardDragged);
	NewCard->OnCancelDragCard.AddDynamic(this, &UCardHandWidget::OnCardDragCancelled);
	//NewCard->OnDragCardEnter.AddDynamic(this, &UCardHandWidget::OnCardDragEnter);
	//NewCard->OnDragCardLeave.AddDynamic(this, &UCardHandWidget::OnCardDragLeave);

	UpdateCardPositions();
}

void UCardHandWidget::RemoveCard(int Index)
{
	if (CardHandOverlay == nullptr) { return; }
	if (Index < 0 || Index >= CardWidgets.Num()) { return; }
	
	CardHandOverlay->RemoveChild(CardWidgets[Index]);
	CardWidgets.RemoveAt(Index);
	
	UpdateCardPositions();
}