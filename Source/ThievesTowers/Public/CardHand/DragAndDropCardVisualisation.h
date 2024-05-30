#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragAndDropCardVisualisation.generated.h"

class ATower;
class UStaticMeshComponent;

UCLASS()
class THIEVESTOWERS_API ADragAndDropCardVisualisation : public AActor
{
	GENERATED_BODY()
	
public:	
	ADragAndDropCardVisualisation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    TSubclassOf<ATower> TowerToSpawn;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyVisualisation();
	virtual void SuppressVisualisation();
};
