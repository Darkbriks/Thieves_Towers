#include "Obstacle.h"
#include "GA_ThievesTowers.h"
#include "MapManager.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(400.0f, 100.0f));

	Tags.Add("Obstacle");
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(), TargetLocation);
	WidgetComponent->SetWorldRotation(TargetRotation);
}

void AObstacle::DestroyObstacle()
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (AMapManager* MapManager = GameInstance->GetMapManager())
		{
			if (MapManager->GetGold() >= ObstacleDestructionCost)
			{
				MapManager->AddGold(-ObstacleDestructionCost);
				Destroy();
			}
		}
	}
}