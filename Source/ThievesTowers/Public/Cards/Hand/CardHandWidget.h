#pragma once

#include "CoreMinimal.h"
#include "CardHandInterface.h"
#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

class UButton;
class ACardEffect;
struct FCardInfo;
class UOverlay;
class UCardWidget;

USTRUCT(Blueprintable)
struct FCardHandParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand Params")
	double ArcLength = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand Params")
	double ArcHeight = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand Params")
	double CardAngle = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand Params")
	float XOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand Params")
	float YOffset = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardPlayed, int, CardIndex, TArray<ACardEffect*>, CardEffects);

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCardHandWidget : public UUserWidget, public ICardHandInterface
{
	GENERATED_BODY()

	bool bCanValidateDeck = false;
	bool bIsPlaying = false;

	int MaxHandSize;
	
	UPROPERTY()
	TArray<UCardWidget*> CardWidgets;

	UPROPERTY()
	UCardWidget* DraggedCardReferance = nullptr;

	UPROPERTY()
	UCardWidget* DragHoveredCard = nullptr;

	UPROPERTY()
	TArray<ACardEffect*> CardEffects;

	static double ArcInterpolation(const double X, const double Y, double T);

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* CardHandOverlay;

	UPROPERTY(meta = (BindWidget))
	UButton* ValidateDeckButton;

	UPROPERTY(BlueprintReadOnly)
	int HoveredCardIndex = -1;

	UPROPERTY(BlueprintReadOnly)
	int ThrowAwayCardIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes - Card Hand")
    TSubclassOf<UCardWidget> CardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes - Card Hand")
	FCardHandParams ValidatingState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes - Card Hand")
	FCardHandParams PlayingState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes - Card Hand")
	float ValidationDelay = 1.0f;

	FCardHandParams* CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Hand - Attributes")
	FWidgetTransform StartTransform;

	virtual void NativeConstruct() override;

	int GetIndexFromCenter(const int Index) const;
	FVector2D GetCenterPosition() const;
	float GetCardXPosition(const int Index);
	float GetCardYPosition(const int Index);
	float GetCardAngle(const int Index) const;

	UFUNCTION(BlueprintCallable)
	void OnValidateDeckButtonClicked();

	UFUNCTION(BlueprintCallable)
	void UpdateCardPositions();

	UFUNCTION(BlueprintCallable)
	void OnCardClicked(UCardWidget* ClickedCard);

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

	void CanValidateDeck();
	bool GetIsPlaying() const { return bIsPlaying; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddCardToHand(FCardInfo NewCard);
	void AddCardToHand_Implementation(FCardInfo NewCard) override { AddCard(NewCard); }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCardFromHand(int Index);
	void RemoveCardFromHand_Implementation(int Index) override { RemoveCard(Index); }
};
