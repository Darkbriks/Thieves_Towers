#include "Path.h"
#include "Components/SplineComponent.h"

APath::APath()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	UpdateSpline();
}

void APath::UpdateSpline()
{
	if (SplinePointCount < 2) { SplinePointCount = 2; }

	if (SplineComponent->GetNumberOfSplinePoints() < SplinePointCount)
	{
		for (int i = SplineComponent->GetNumberOfSplinePoints(); i < SplinePointCount; i++)
		{
			SplineComponent->AddSplinePoint(FVector(i * 100, 0, 0), ESplineCoordinateSpace::Local);
		}
	}
	else if (SplineComponent->GetNumberOfSplinePoints() > SplinePointCount)
	{
		for (int i = SplineComponent->GetNumberOfSplinePoints(); i > SplinePointCount; i--)
		{
			SplineComponent->RemoveSplinePoint(i - 1);
		}
	}

	SplineComponent->SetLocationAtSplinePoint(SplinePointCount - 1, EndPoint, ESplineCoordinateSpace::World);
}

void APath::SetEndPointLocation()
{
	if (SplineComponent->GetNumberOfSplinePoints() > 0)
	{
		EndPoint = SplineComponent->GetLocationAtSplinePoint(SplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	}
}

void APath::BeginPlay()
{
	Super::BeginPlay();
	SplinePointCount = SplineComponent->GetNumberOfSplinePoints();

	if (NextPath == this)
	{
		NextPath = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("NextPath cannot be the same as this path. NextPath has been set to nullptr."));
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("NextPath cannot be the same as this path. NextPath has been set to nullptr."));
	}
}