#pragma once

#include "CoreMinimal.h"
#include "Enum/TypeOfDamage.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

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

	UPROPERTY()
	AEnemy* TargetEnemy = nullptr;

	bool bIsInitialized = false;
	bool bIsLaunched = false;
	TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile - Components")
	UArrowComponent* ArrowComponent;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	float Speed = 5000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile - Attributes")
	bool bLockOnTarget = true;

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
	void InitializeProjectile(FVector NewTargetPosition, AEnemy* NewTargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> NewAdditionalTypesOfDamage);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Launch();
	
	virtual void Tick(float DeltaTime) override;
};
