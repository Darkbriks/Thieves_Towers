#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/CardInfo.h"
#include "Components/Image.h"
#include "CardWidget.generated.h"

class UCardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoverCard, UCardWidget*, HoveredCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnhoverCard, UCardWidget*, UnhoveredCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragCard, UCardWidget*, DraggedCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCancelDragCard, UCardWidget*, CancelDraggedCard, bool, bDragIsCancelled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragCardEnter, UCardWidget*, HoveredCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragCardLeave, UCardWidget*, UnhoveredCard);

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

	FWidgetTransform TargetTransform;
	bool bIsMoving = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes", meta = (ExposeOnSpawn = true))
	FCardInfo CardInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	float HoverScale = 1.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	float UnhoverScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FVector2D HoverOffset = FVector2D(100.0f, -100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FVector2D UnhoverOffset = FVector2D(0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	float DraggableOpacity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	float InterpolationSpeed = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FVector2D CardSize = FVector2D(160.0f, 256.0f);
	
	UPROPERTY(meta = (BindWidget))
	class UImage* CardImage;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	

public:
	UPROPERTY(BlueprintAssignable)
	FOnHoverCard OnHoverCard;

	UPROPERTY(BlueprintAssignable)
	FOnUnhoverCard OnUnhoverCard;

	UPROPERTY(BlueprintAssignable)
	FOnDragCard OnDragCard;

	UPROPERTY(BlueprintAssignable)
	FOnCancelDragCard OnCancelDragCard;

	UPROPERTY(BlueprintAssignable)
	FOnDragCardEnter OnDragCardEnter;

	UPROPERTY(BlueprintAssignable)
	FOnDragCardLeave OnDragCardLeave;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartMoving(FWidgetTransform NewTransform);

	UFUNCTION(BlueprintCallable)
	FCardInfo GetCardInfo() { return CardInfo; }

	UFUNCTION(BlueprintCallable)
	float GetHoverScale() { return HoverScale; }

	UFUNCTION(BlueprintCallable)
	float GetUnhoverScale() { return UnhoverScale; }

	UFUNCTION(BlueprintCallable)
	FVector2D GetHoverOffset() { return HoverOffset; }

	UFUNCTION(BlueprintCallable)
	FVector2D GetUnhoverOffset() { return UnhoverOffset; }

	UFUNCTION(BlueprintCallable)
	FVector2D GetCardSize() { return CardSize; }

	UFUNCTION(BlueprintCallable)
	void SetCardInfo(FCardInfo NewCardInfo) { CardInfo = NewCardInfo; }
};
