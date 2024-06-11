#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UWidgetComponent;

UCLASS()
class THIEVESTOWERS_API AObstacle : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle - Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle - Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle - Attributes")
	FName ObstacleName = "Obstacle";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle - Attributes")
	int ObstacleDestructionCost = 0;

public:
	AObstacle();

	virtual void Tick(float DeltaTime) override;
};