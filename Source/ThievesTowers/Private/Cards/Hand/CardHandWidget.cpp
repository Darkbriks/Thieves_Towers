#include "Cards/Hand/CardHandWidget.h"
#include "Cards/Hand/CardWidget.h"
#include "Cards/Effects/CardEffect.h"
#include "Manager/GA_ThievesTowers.h"
#include "Components/Overlay.h"
#include "Components/Button.h"

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

			ValidateDeckButton->OnClicked.AddDynamic(this, &UCardHandWidget::OnValidateDeckButtonClicked);
			ValidateDeckButton->SetVisibility(ESlateVisibility::Hidden);

			CurrentState = &ValidatingState;

			MaxHandSize = MapManager->GetMaxHandSize();
		}
	}
}

double UCardHandWidget::ArcInterpolation(const double X, const double Y, double T)
{
	// Assurer que t reste dans l'intervalle [0, x]
	if (T < 0.0) T = 0.0;
	if (T > X) T = X;

	// Calcul de la position sur l'arc de cercle
	double theta = (T / X) * PI; // Angle de l'arc au point t
	double result = Y * std::sin(theta); // Hauteur de l'arc au point t

	return result;
}

int UCardHandWidget::GetIndexFromCenter(const int Index) const
{
	if (CardHandOverlay == nullptr) { return 0; }
	if (CardWidgets.Num() == 1) { return 0; }
	return FMath::Lerp(-(CardWidgets.Num() - 1), CardWidgets.Num() - 1, Index / static_cast<float>(CardWidgets.Num() - 1));
}

FVector2D UCardHandWidget::GetCenterPosition() const
{
	if (CardHandOverlay == nullptr) { return FVector2D(); }
	return CardHandOverlay->GetCachedGeometry().GetLocalSize() / 2.0f;
}

float UCardHandWidget::GetCardXPosition(const int Index)
{
	if (CardHandOverlay == nullptr) { return 0.0f; }
	if (CardWidgets.Num() == 1) { return GetCenterPosition().X - (CardWidgets[Index]->GetCardSize().X / 2.0f); }
	const double Length = CurrentState->ArcLength * (CardWidgets.Num() / static_cast<double>(MaxHandSize));
	return GetCenterPosition().X - (Length / 2.0f) + (Index / static_cast<double>(CardWidgets.Num() - 1)) * Length - CardWidgets[Index]->GetCardSize().X / 2.0f;
}

float UCardHandWidget::GetCardYPosition(const int Index)
{
	if (CardHandOverlay == nullptr) { return 0.0f; }
	double InterpIndex = 0.0;
	if (CardWidgets.Num() > 1) { InterpIndex = (Index / static_cast<double>(CardWidgets.Num() - 1)) * CurrentState->ArcLength; }
	const double Height = CurrentState->ArcHeight * (CardWidgets.Num() / static_cast<double>(MaxHandSize));
	return GetCenterPosition().Y - ArcInterpolation(CurrentState->ArcLength, Height, InterpIndex) - CardWidgets[Index]->GetCardSize().Y / 2.0f - CurrentState->YOffset;
}

float UCardHandWidget::GetCardAngle(const int Index) const { return GetIndexFromCenter(Index) * CurrentState->CardAngle; }

void UCardHandWidget::OnValidateDeckButtonClicked()
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			MapManager->InitRound();
			this->CanPlay();
			ValidateDeckButton->RemoveFromParent();
			ValidateDeckButton->ConditionalBeginDestroy();
		}
	}
}

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
	if (CardHandOverlay == nullptr || !bIsPlaying) { return; }
	HoveredCardIndex = CardWidgets.Find(HoveredCard);
	UpdateCardPositions();
}

void UCardHandWidget::OnCardUnhovered(UCardWidget* UnhoveredCard)
{
	if (CardHandOverlay == nullptr || !bIsPlaying) { return; }
	if (HoveredCardIndex == CardWidgets.Find(UnhoveredCard)) { HoveredCardIndex = -1; UpdateCardPositions(); }
}

void UCardHandWidget::OnCardDragged(UCardWidget* DraggedCard)
{
	if (CardHandOverlay == nullptr || !bIsPlaying) { return; }
	this->DraggedCardReferance = DraggedCard;

	TArray<TSubclassOf<ACardEffect>> Effects = DraggedCard->GetCardInfo().GetEffects();
	CardEffects.SetNum(Effects.Num());
	for (int i = 0; i < Effects.Num(); i++)
	{
		if (Effects[i] == nullptr) { continue; }
		CardEffects[i] = GetWorld()->SpawnActor<ACardEffect>(Effects[i]);
		if (CardEffects[i] == nullptr) { UE_LOG(LogTemp, Error, TEXT("CardEffect is null")); }
	}
}

void UCardHandWidget::OnCardDragCancelled(UCardWidget* CancelDraggedCard, bool bDragIsCancelled)
{
	if (CardHandOverlay == nullptr || !bIsPlaying || bDragIsCancelled) { for (ACardEffect* CardEffect : CardEffects) { CardEffect->CancelEffect(); } return; }
	if (DraggedCardReferance == CancelDraggedCard) { DraggedCardReferance = nullptr; }
	OnCardPlayed.Broadcast(CardWidgets.Find(CancelDraggedCard), CardEffects);
}

void UCardHandWidget::OnCardDragEnter(UCardWidget* HoveredCard)
{
	if (CardHandOverlay == nullptr || !bIsPlaying) { return; }
	DragHoveredCard = HoveredCard;
}

void UCardHandWidget::OnCardDragLeave(UCardWidget* UnhoveredCard)
{
	if (CardHandOverlay == nullptr || !bIsPlaying) { return; }
	if (DragHoveredCard == UnhoveredCard) { DragHoveredCard = nullptr; }
}

void UCardHandWidget::AddCard(FCardInfo Card)
{
	if (CardHandOverlay == nullptr) { return; }
	
	UCardWidget* NewCard = CreateWidget<UCardWidget>(this, CardWidgetClass);
	NewCard->SetCardInfo(Card);
	CardHandOverlay->AddChild(NewCard);
	CardWidgets.Add(NewCard);
	NewCard->SetRenderTransform(StartTransform);
	
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

void UCardHandWidget::CanValidateDeck()
{
	if (bCanValidateDeck || bIsPlaying) { return; }
	bCanValidateDeck = true;
	ValidateDeckButton->SetVisibility(ESlateVisibility::Visible);
}

void UCardHandWidget::CanPlay()
{
	if (!bCanValidateDeck || bIsPlaying) { return; }
	bCanValidateDeck = false;
	bIsPlaying = true;
	CurrentState = &PlayingState;
	UpdateCardPositions();
}