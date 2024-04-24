#pragma once

#include "CoreMinimal.h"

#include "Enum/Rarity.h"

#include "GameFramework/Actor.h"
#include "Card.generated.h"

class UPaperSpriteComponent;
class UCardEffect;

UCLASS(Blueprintable)
class THIEVESTOWERS_API ACard : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FName CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TEnumAsByte<ERarity> Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	int GoldCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card - Attributes")
	TArray<TSubclassOf<UCardEffect>> Effects;

	void BeginPlay() override;

	UFUNCTION()
	void OnHovered(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnUnhovered(UPrimitiveComponent* TouchedComponent);
	
public:
	ACard();
};
