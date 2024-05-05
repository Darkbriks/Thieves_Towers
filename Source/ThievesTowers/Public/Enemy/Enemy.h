#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

enum EEnemyType : int;
enum ETypeOfDamage : int;
class UPaperSpriteComponent;
class AProjectile;
class APath;

UCLASS()
class THIEVESTOWERS_API AEnemy : public AActor
{
	GENERATED_BODY()

	// Variables
	int StartLife = 0;
	int Life = 0;
	int LifeOverflows = 0;

	float RemainingHealTime = 0.0f;

	float RemainingFreezeTime = 0.0f;
	int DamageAfterFreeze = 0;
	TArray<TEnumAsByte<ETypeOfDamage>> FreezeTypesOfDamage = TArray<TEnumAsByte<ETypeOfDamage>>();
	
	TArray<AProjectile*> Projectiles;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy - Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy - Components", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	
protected:
	float CurrentPathDistance = 0.0f;
	float CurrentPathLength = 0.0f;
	float TraveledDistance = 0.0f;
	float TotalDistance = 0.0f;
	APath* CurrentPath = nullptr;

	bool bCanBeTargeted = true;

	UMaterialInstanceDynamic* DynamicMaterial = nullptr;
	
	// Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int MaxLife = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float Speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	TEnumAsByte<EEnemyType> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	TArray<TEnumAsByte<ETypeOfDamage>> Resistances;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float TargetZOffset = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
    FColor HealColor = FColor(168, 202, 88, 255);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float HealEffectTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	float HealEffectAlpha = 0.5f;

	// Getters
	UPaperSpriteComponent* GetSpriteComponent() const { return SpriteComponent; }
	int GetLifeOverflows() const { return LifeOverflows; }

	// Methods
	void MoveAlongPath(float DeltaTime);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Die(bool bExecuteByTower);
	
public:
	// Constructor
	AEnemy();

	virtual void InitializeEnemy(APath* NewPath, float NewCurrentDistance = 0.0f);

	// Getters
	int GetMaxLife() const { return MaxLife; }
	int GetLife() const { return Life; }
	int GetDamage() const { return Damage; }
	float GetSpeed() const { return Speed; }
	TEnumAsByte<EEnemyType> GetEnemyType() const { return EnemyType; }
	TArray<TEnumAsByte<ETypeOfDamage>> GetResistances() const { return Resistances; }
	float GetTargetZOffset() const { return TargetZOffset; }
	bool CanBeTargeted() const { return bCanBeTargeted; }
	
	float GetCurrentPathDistance() const { return CurrentPathDistance; }
	float GetTraveledDistance() const { return TraveledDistance; }
	float GetTotalDistance() const { return TotalDistance; }
	APath* GetCurrentPath() const { return CurrentPath; }

	TArray<AProjectile*> GetProjectiles() const { return Projectiles; }

	// Setters
	void SetMaxLife(int NewMaxLife) { MaxLife = FMath::Max(1, NewMaxLife); }
	void SetLife(int NewLife) { Life = FMath::Clamp(NewLife, 1, MaxLife); }
	void SetLifeOverflows(int NewLifeOverflows) { LifeOverflows = NewLifeOverflows; }

	// Methods
	void Heal(int HealAmount);
	virtual void TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void Freeze(float FreezeTime, FColor FreezeColor, int NewDamageAfterFreeze = 0, TArray<TEnumAsByte<ETypeOfDamage>> NewTypesOfDamage = TArray<TEnumAsByte<ETypeOfDamage>>());
	void AddProjectile(AProjectile* NewProjectile) { Projectiles.Add(NewProjectile); }

	// Overriden methods
	virtual void Tick(float DeltaTime) override;
};