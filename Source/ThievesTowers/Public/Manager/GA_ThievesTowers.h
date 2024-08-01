#pragma once

#include "CoreMinimal.h"
#include "MapManager.h"
#include "Engine/GameInstance.h"
#include "GA_ThievesTowers.generated.h"

class AEnemy_Silly;
class AEnemy;
class APrimitiveTower;
class UProjectileEffect;

UCLASS()
class THIEVESTOWERS_API UGA_ThievesTowers : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MapManager", meta = (AllowPrivateAccess = "true"))
	AMapManager* MapManager;

	TArray<UProjectileEffect*> ProjectileEffects;
	TArray<APrimitiveTower*> Towers;

	UPROPERTY()
	TArray<AEnemy*> Enemies;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AMapManager* GetMapManager() { if (!MapManager) { MapManager = GetWorld()->SpawnActor<AMapManager>(); } return MapManager; }
	
	UFUNCTION(BlueprintCallable)
	void SetMapManager(AMapManager* NewMapManager) { this->MapManager = NewMapManager; }
	
	// Methods
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULightningEffect, STATGROUP_Tickables); }

	// Delegates
	FDelegateHandle TickDelegateHandle;

	// Getters
	UProjectileEffect* GetProjectileEffect(TSubclassOf<UProjectileEffect> EffectClass);
	TArray<AEnemy*> GetEnemies() { return Enemies; }
	int GetNumberEnemiesOfType(TSubclassOf<AEnemy> EnemyClass);
	int GetNumberEnemiesOfTypeInRange(TSubclassOf<AEnemy> EnemyClass, FVector Location, float Range);

	UFUNCTION(BlueprintCallable)
	void AddTower(APrimitiveTower* Tower);
	void RemoveTower(APrimitiveTower* Tower);
	void AddEnemy(AEnemy* Enemy);
	void RemoveEnemy(AEnemy* Enemy);
};