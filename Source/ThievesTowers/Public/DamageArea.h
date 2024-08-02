#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles/TypeOfDamage.h"
#include "DamageArea.generated.h"

class USphereComponent;
class AEnemy;

UCLASS()
class THIEVESTOWERS_API ADamageArea : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	float DamageCooldown = 0.0f;
	float CreationTime = 0.0f;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	bool bUseBoxCollision = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area", meta = (EditCondition = "bUseBoxCollision"))
	FVector BoxExtent = FVector(50.0f, 50.0f, 50.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area", meta = (EditCondition = "!bUseBoxCollision"))
	float SphereRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	int Damage = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	float DamageInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	bool bCooldownBeforeFirstDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
    bool bInfinitely = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area" , meta = (EditCondition = "!bInfinitely"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area")
	bool bApplyColorEffect = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area", meta = (EditCondition = "bApplyColorEffect"))
	float ColorEffectDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area", meta = (EditCondition = "bApplyColorEffect"))
	float ColorEffectAlpha = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Area", meta = (EditCondition = "bApplyColorEffect"))
	FColor ColorEffect = FColor::White;	

public:
	ADamageArea();
	
	virtual void Tick(float DeltaTime) override;
};
