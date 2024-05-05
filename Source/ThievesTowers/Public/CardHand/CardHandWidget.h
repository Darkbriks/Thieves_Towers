#pragma once

#include "CoreMinimal.h"
#include "CardHandInterface.h"

#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

class ADragAndDropCardVisualisation;
struct FCardInfo;
class UOverlay;
class UCardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardPlayed, int, CardIndex);

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCardHandWidget : public UUserWidget, public ICardHandInterface
{
	GENERATED_BODY()

	TArray<UCardWidget*> CardWidgets;
	int HoveredCardIndex = -1;
	UCardWidget* DraggedCardReferance = nullptr;
	UCardWidget* DragHoveredCard = nullptr;
	ADragAndDropCardVisualisation* DragAndDropCardVisualisation = nullptr;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	UDataTable* CardDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	TSubclassOf<ADragAndDropCardVisualisation> DragAndDropCardVisualisationClass;

	virtual void NativeConstruct() override;

	FCardInfo GetRandomCard();

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
	void OnCardDragCancelled(UCardWidget* CancelDraggedCard);

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
