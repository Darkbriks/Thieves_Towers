#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

class UCapsuleComponent;
class AProjectile;

UCLASS()
class THIEVESTOWERS_API ATower : public AActor
{
	GENERATED_BODY()

	float AttackCooldown = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float AttackRange = 2000.0f;

	bool Attack();

	virtual void BeginPlay() override;

public:	
	ATower();
	
	virtual void Tick(float DeltaTime) override;

};
