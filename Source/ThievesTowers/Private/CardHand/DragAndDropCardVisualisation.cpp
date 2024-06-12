#include "CardHand/DragAndDropCardVisualisation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Tower.h"

ADragAndDropCardVisualisation::ADragAndDropCardVisualisation()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetMobility(EComponentMobility::Movable);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Root);
	Sphere->SetSphereRadius(100.0f);
	Sphere->SetCollisionProfileName("OverlapAllDynamic");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADragAndDropCardVisualisation::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADragAndDropCardVisualisation::OnOverlapEnd);

	OverlappingObstacles = TArray<AActor*>();
}

void ADragAndDropCardVisualisation::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Obstacle") || OtherComp->ComponentHasTag("Tower-Basement"))
	{
		OverlappingObstacles.Add(OtherActor);
	}
}

void ADragAndDropCardVisualisation::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Obstacle") || OtherComp->ComponentHasTag("Tower-Basement"))
	{
		OverlappingObstacles.Remove(OtherActor);
	}
}

void ADragAndDropCardVisualisation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCanSpawn = false;

	FVector WorldPosition;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), UWidgetLayoutLibrary::GetMousePositionOnViewport(this) * UWidgetLayoutLibrary::GetViewportScale(this), WorldPosition, WorldDirection);

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(), WorldPosition, WorldPosition + WorldDirection * 10000.0f, ETraceTypeQuery::TraceTypeQuery1, false, { this }, EDrawDebugTrace::None, HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
	if (HitResults.Num() > 0)
	{
		// On cherche le premier objet qui possède le tag "floor"
		for (FHitResult HitResult : HitResults)
		{
			SetActorLocation(HitResult.ImpactPoint);
			if (OverlappingObstacles.Num() == 0 && HitResult.GetActor()->ActorHasTag("Floor") && HitResult.Normal.Z >= 0.9f)
			{
				Mesh->SetRenderCustomDepth(false);
				bCanSpawn = true;
				return;
			}
		}
		Mesh->SetRenderCustomDepth(true);
		return;
	}
	this->SetActorLocation(WorldPosition + WorldDirection * 1000.0f);
}

bool ADragAndDropCardVisualisation::ApplyVisualisation()
{
	if (TowerToSpawn && !bCanSpawn) { Destroy(); return false; }
	GetWorld()->SpawnActor<ATower>(TowerToSpawn, GetActorLocation(), FRotator::ZeroRotator);
	Destroy(); return true;
}

void ADragAndDropCardVisualisation::SuppressVisualisation()
{
	Destroy();
}