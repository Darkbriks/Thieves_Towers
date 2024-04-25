#pragma once

#include "CoreMinimal.h"
#include "TD_Player.h"
#include "Engine/GameInstance.h"
#include "GA_ThievesTowers.generated.h"

class AEnemy_Silly;
class AEnemy;
class ATower;
class UProjectileEffect;
class ACard;

UCLASS()
class THIEVESTOWERS_API UGA_ThievesTowers : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

	TArray<UProjectileEffect*> ProjectileEffects;

	// Card
	int MaxHandSize = 8;
	TArray<TSubclassOf<ACard>> Hand;

	TArray<ATower*> Towers;

	TArray<AEnemy*> Enemies;

public:
	// Methods
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULightningEffect, STATGROUP_Tickables); }

	// Delegates
	FCreateHandDelegate CreateHandDelegate;
	FDelegateHandle TickDelegateHandle;

	// Getters
	UProjectileEffect* GetProjectileEffect(TSubclassOf<UProjectileEffect> EffectClass);
	int GetMaxHandSize() { return MaxHandSize; }
	TArray<TSubclassOf<ACard>> GetHand() { return Hand; }
	TArray<AEnemy*> GetEnemies() { return Enemies; }

	UFUNCTION(BlueprintCallable)
	void AddCardToHand(TSubclassOf<ACard> CardClass);
	void RemoveCardFromHand(TSubclassOf<ACard> CardClass);
	void AddTower(ATower* Tower);
	void RemoveTower(ATower* Tower);
	void AddEnemy(AEnemy* Enemy);
	void RemoveEnemy(AEnemy* Enemy);
};