#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

enum ETypeOfDamage : int;
class UPaperSpriteComponent;
class UProjectileEffect;
class UArrowComponent;
class AEnemy;

UCLASS()
class THIEVESTOWERS_API AProjectile : public AActor
{
	GENERATED_BODY()

	FVector InitialPosition;
	FVector TargetPosition;
	AEnemy* TargetEnemy = nullptr;

	bool bIsInitialized = false;
	bool bIsLaunched = false;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	UArrowComponent* ArrowComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	float Speed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	bool bLockOnTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	float Epsilon = 10.0f;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void MoveTowardsTarget(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Impact();

	FRotator const GetLookAtRotation(FVector Start, FVector Target);
	
public:	
	AProjectile();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void InitializeProjectile(FVector NewTargetPosition, AEnemy* NewTargetEnemy);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Launch();
	
	virtual void Tick(float DeltaTime) override;
};
