#include "CardHand/CardWidget.h"
#include "Components/Image.h"
#include "Struct/CardInfo.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

//////////////////////////////////////////////////////////////////////////
/// UCardWidget - Protected
//////////////////////////////////////////////////////////////////////////
void UCardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CardImage != nullptr && CardInfo.GetCardTexture() != nullptr)
	{
		CardImage->SetBrushFromTexture(CardInfo.GetCardTexture());
	}
}

FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return Reply.NativeReply;
}

void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) { OnHoverCard.Broadcast(this); }
void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) { OnUnhoverCard.Broadcast(this); }

void UCardWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	this->SetRenderOpacity(DraggableOpacity);

	// Create the drag operation
	UDragDropOperation* Operation = NewObject<UDragDropOperation>();
	Operation->Payload = this;
	Operation->DefaultDragVisual = this;
	Operation->Pivot = EDragPivot::MouseDown;
	OutOperation = Operation;
	
	OnDragCard.Broadcast(this);
}

void UCardWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bDragIsCancelled = false; // TODO: True si le bouton droit de la souris a été relâché
	this->SetRenderOpacity(1.0f);
	OnCancelDragCard.Broadcast(this, bDragIsCancelled);
}

void UCardWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) { OnDragCardEnter.Broadcast(this); }
void UCardWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) { OnDragCardLeave.Broadcast(this); }

//////////////////////////////////////////////////////////////////////////
/// UCardWidget - Public
//////////////////////////////////////////////////////////////////////////
void UCardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bIsMoving) { return; }

	// Interpolate the position
	FVector2D NewPosition = FMath::Vector2DInterpTo(this->GetRenderTransform().Translation, TargetTransform.Translation, InDeltaTime, InterpolationSpeed);
	FVector2D NewScale = FMath::Vector2DInterpTo(this->GetRenderTransform().Scale, TargetTransform.Scale, InDeltaTime, InterpolationSpeed);
	float NewAngle = FMath::FInterpTo(this->GetRenderTransform().Angle, TargetTransform.Angle, InDeltaTime, InterpolationSpeed);

	// Set the new position
	this->SetRenderTranslation(NewPosition);
	this->SetRenderScale(NewScale);
	this->SetRenderTransformAngle(NewAngle);

	if (NewPosition == TargetTransform.Translation && NewAngle == TargetTransform.Angle) { bIsMoving = false; }
}

void UCardWidget::StartMoving(FWidgetTransform NewTransform)
{
	TargetTransform = NewTransform;
	bIsMoving = true;
}