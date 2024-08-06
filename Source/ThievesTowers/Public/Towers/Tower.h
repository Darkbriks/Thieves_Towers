#pragma once

#include "CoreMinimal.h"
#include "PrimitiveTower.h"
#include "Towers/Targeting/FirstEnemyInRange.h"
#include "Towers/Targeting/LastEnemyInRange.h"
#include "Towers/Targeting/Closer.h"
#include "Towers/Targeting/Further.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

class UTargetingMode;
class AEnemy;
class AProjectile;
class UPaperFlipbook;
class UPaperFlipbookComponent;

UCLASS()
class THIEVESTOWERS_API ATower : public APrimitiveTower
{
	GENERATED_BODY()

	UPROPERTY()
	UTargetingMode* TargetingMode;

	float AttackCooldown = 0.0f;
	float AnimationCooldown = 0.0f;
	float AnimationOverflow = 0.0f;
	FRotator TargetRotation;

	UPROPERTY()
	TArray<AEnemy*> EnemiesInRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BasementMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	TSubclassOf<AProjectile> ProjectileClass;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
    //TSubclassOf<UTargetingMode> CurrentTargetingModeClass = UFirstEnemyInRange::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	TArray<TSubclassOf<UTargetingMode>> TargetingModes = {
		UFirstEnemyInRange::StaticClass(),
		ULastEnemyInRange::StaticClass(),
		UCloser::StaticClass(),
		UFurther::StaticClass()
	};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float AttackSpeed = 1.0f;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Animation")
	float RotationSpeed = 250.0f;
	
	AEnemy* GetEnemyInRange();
	void Anim(float DeltaTime);
	virtual bool Attack();
	
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void BeginPlay() override;

public:	
	ATower();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Deactivate() override;

	virtual TArray<TSubclassOf<UTargetingMode>> GetTargetingModes() { return TargetingModes; }
	virtual TSubclassOf<UTargetingMode> GetCurrentTargetingMode() { return TargetingMode->GetClass(); }
	virtual void SetTargetingMode(const TSubclassOf<UTargetingMode> InTargetingMode);
};
