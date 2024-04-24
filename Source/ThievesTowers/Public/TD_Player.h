#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TD_Player.generated.h"

class UGA_ThievesTowers;
class ACard;
class USceneComponent;
class UCameraComponent;
class USplineComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DELEGATE_OneParam(FCreateHandDelegate, TArray<TSubclassOf<ACard>>);

UCLASS()
class THIEVESTOWERS_API ATD_Player : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USplineComponent* CardHandSpline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* CardHandSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UpDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float LookSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float UpDownSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	FVector CardScale = FVector(0.15f, 0.15f, 0.15f);

	UGA_ThievesTowers* TT_GameInstance;

	TArray<FVector> CardHandPositions;
	TArray<FRotator> CardHandRotations;
	TArray<ACard*> CardsInHand;
	
protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void UpDown(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void CreateHand(TArray<TSubclassOf<ACard>> NewHand);

public:
	FCreateHandDelegate UpdateHandDelegate = FCreateHandDelegate();
	
	ATD_Player();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};