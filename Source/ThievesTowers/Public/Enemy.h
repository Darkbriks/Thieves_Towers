#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

enum EEnemyType : int;
enum ETypeOfDamage : int;
class UPaperSpriteComponent;
class UWidgetComponent;
class AProjectile;
class APath;

UCLASS()
class THIEVESTOWERS_API AEnemy : public AActor
{
	GENERATED_BODY()

	// Variables
	int Health = 0;

	float RemainingFreezeTime = 0.0f;
	int DamageAfterFreeze = 0;
	TArray<TEnumAsByte<ETypeOfDamage>> FreezeTypesOfDamage = TArray<TEnumAsByte<ETypeOfDamage>>();
	
	float CurrentPathDistance = 0.0f;
	float CurrentPathLength = 0.0f;
	float TraveledDistance = 0.0f;
	float TotalDistance = 0.0f;
	APath* CurrentPath = nullptr;

	UMaterialInstanceDynamic* DynamicMaterial = nullptr;
	
	TArray<AProjectile*> Projectiles;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy - Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy - Components", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	
protected:
	// Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy - Attributes")
	int StartHealth = 1;

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

	// Methods
	void MoveAlongPath(float DeltaTime);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Die();
	
public:
	// Constructor
	AEnemy();

	void InitializeEnemy(APath* NewPath, float NewCurrentDistance = 0.0f);

	// Getters
	int GetStartHealth() const { return StartHealth; }
	int GetHealth() const { return Health; }
	int GetDamage() const { return Damage; }
	float GetSpeed() const { return Speed; }
	TEnumAsByte<EEnemyType> GetEnemyType() const { return EnemyType; }
	TArray<TEnumAsByte<ETypeOfDamage>> GetResistances() const { return Resistances; }
	float GetTargetZOffset() const { return TargetZOffset; }
	
	float GetCurrentPathDistance() const { return CurrentPathDistance; }
	float GetTraveledDistance() const { return TraveledDistance; }
	float GetTotalDistance() const { return TotalDistance; }
	APath* GetCurrentPath() const { return CurrentPath; }

	TArray<AProjectile*> GetProjectiles() const { return Projectiles; }

	// Setters
	//void SetFreezeTime(float NewFreezeTime) { RemainingFreezeTime = NewFreezeTime; }

	// Methods
	void TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void Freeze(float FreezeTime, FColor FreezeColor, int NewDamageAfterFreeze = 0, TArray<TEnumAsByte<ETypeOfDamage>> NewTypesOfDamage = TArray<TEnumAsByte<ETypeOfDamage>>());
	void AddProjectile(AProjectile* NewProjectile) { Projectiles.Add(NewProjectile); }

	// Overriden methods
	virtual void Tick(float DeltaTime) override;
};