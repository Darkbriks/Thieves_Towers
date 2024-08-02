#pragma once

#include "CoreMinimal.h"
#include "Projectiles/TypeOfDamage.h"
#include "GameFramework/Actor.h"
#include "PrimitiveTower.generated.h"

class UCapsuleComponent;
class USphereComponent;

UCLASS()
class THIEVESTOWERS_API APrimitiveTower : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
	bool bIsActivated = true;

	TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	float Range = 2000.0f;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	APrimitiveTower();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Activate();

	UFUNCTION(BlueprintCallable)
	virtual void Deactivate();

	UFUNCTION(BlueprintCallable)
	virtual void AddAdditionalTypeOfDamage(TEnumAsByte<ETypeOfDamage> TypeOfDamage) { AdditionalTypesOfDamage.Add(TypeOfDamage); }

	UFUNCTION(BlueprintCallable)
	virtual void RemoveAdditionalTypeOfDamage(TEnumAsByte<ETypeOfDamage> TypeOfDamage) { for (int i = 0; i < AdditionalTypesOfDamage.Num(); i++) { if (AdditionalTypesOfDamage[i] == TypeOfDamage) { AdditionalTypesOfDamage.RemoveAt(i); return; } } }
};
