#pragma once

#include "CoreMinimal.h"
#include "TD_Player.h"
#include "Engine/GameInstance.h"
#include "GA_ThievesTowers.generated.h"

class UProjectileEffect;
class ACard;



UCLASS()
class THIEVESTOWERS_API UGA_ThievesTowers : public UGameInstance
{
	GENERATED_BODY()

	TArray<UProjectileEffect*> ProjectileEffects;

	int MaxHandSize = 8;
	TArray<TSubclassOf<ACard>> Hand;

public:
	// Methods
	void Init() override;
	void Shutdown() override;
	void Tick(float DeltaTime);

	// Delegates
	FCreateHandDelegate CreateHandDelegate;
	FDelegateHandle TickDelegateHandle;

	// Getters
	UProjectileEffect* GetProjectileEffect(TSubclassOf<UProjectileEffect> EffectClass);
	int GetMaxHandSize() { return MaxHandSize; }
	TArray<TSubclassOf<ACard>> GetHand() { return Hand; }

	UFUNCTION(BlueprintCallable)
	void AddCardToHand(TSubclassOf<ACard> CardClass);
	void RemoveCardFromHand(TSubclassOf<ACard> CardClass);
};