#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

class AEnemy;
class UCapsuleComponent;
class AProjectile;
class UPaperFlipbook;
class UPaperFlipbookComponent;

UCLASS()
class THIEVESTOWERS_API ATower : public AActor
{
	GENERATED_BODY()

	float AttackCooldown = 0.0f;
	float AttackAnimationTotalTime = 0.0f;
	float AttackAnimationCurrentTime = 0.0f;
	TArray<AEnemy*> EnemiesInRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float AttackRange = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float ProjectileXOffset = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float ProjectileYOffset = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float ProjectileZOffset = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Animation")
	UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Animation")
	UPaperFlipbook* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Animation", meta = (ToolTip = "Time in seconds to launch the projectile after the attack animation starts"))
	float ProjectileLaunchTime = 0.5f;
	
	bool Attack();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void BeginPlay() override;

public:	
	ATower();
	
	virtual void Tick(float DeltaTime) override;

};
