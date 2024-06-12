#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragAndDropCardVisualisation.generated.h"

class USphereComponent;
class ATower;
class UStaticMeshComponent;

UCLASS()
class THIEVESTOWERS_API ADragAndDropCardVisualisation : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATower> TowerToSpawn;

	bool bCanSpawn = false;
	TArray<AActor*> OverlappingObstacles;

public:
	ADragAndDropCardVisualisation();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyVisualisation();
	virtual void SuppressVisualisation();
};
