#include "Obstacle.h"
#include "Components/WidgetComponent.h"

#include "Kismet/KismetMathLibrary.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(), TargetLocation);
	WidgetComponent->SetWorldRotation(TargetRotation);
}