#pragma once

#include "CoreMinimal.h"
#include "CardHandInterface.h"
#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

class ACardEffect;
struct FCardInfo;
class UOverlay;
class UCardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardPlayed, int, CardIndex, TArray<ACardEffect*>, CardEffects);

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCardHandWidget : public UUserWidget, public ICardHandInterface
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UCardWidget*> CardWidgets;

	UPROPERTY()
	int HoveredCardIndex = -1;

	UPROPERTY()
	UCardWidget* DraggedCardReferance = nullptr;

	UPROPERTY()
	UCardWidget* DragHoveredCard = nullptr;

	UPROPERTY()
	TArray<ACardEffect*> CardEffects;

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* CardHandOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
    TSubclassOf<UCardWidget> CardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	float CardAngle = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	float XArcRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	float YArcRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	float ZOffset = -550.0f;

	virtual void NativeConstruct() override;

	int GetIndexFromCenter(int Index);
	FVector2D GetCenterPosition();
	float GetCardXPosition(int Index);
	float GetCardYPosition(int Index);
	float GetCardAngle(int Index);

	UFUNCTION(BlueprintCallable)
	void UpdateCardPositions();

	UFUNCTION(BlueprintCallable)
	void OnCardHovered(UCardWidget* HoveredCard);

	UFUNCTION(BlueprintCallable)
	void OnCardUnhovered(UCardWidget* UnhoveredCard);

	UFUNCTION(BlueprintCallable)
	void OnCardDragged(UCardWidget* DraggedCard);

	UFUNCTION(BlueprintCallable)
	void OnCardDragCancelled(UCardWidget* CancelDraggedCard, bool bDragIsCancelled);

	UFUNCTION(BlueprintCallable)
	void OnCardDragEnter(UCardWidget* HoveredCard);

	UFUNCTION(BlueprintCallable)
	void OnCardDragLeave(UCardWidget* UnhoveredCard);

	UFUNCTION(BlueprintCallable)
	void AddCard(FCardInfo Card);

	UFUNCTION(BlueprintCallable)
	void RemoveCard(int Index);

public:
	UPROPERTY(BlueprintAssignable)
	FOnCardPlayed OnCardPlayed;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddCardToHand(FCardInfo NewCard);
	void AddCardToHand_Implementation(FCardInfo NewCard) override { AddCard(NewCard); }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCardFromHand(int Index);
	void RemoveCardFromHand_Implementation(int Index) override { RemoveCard(Index); }
};
