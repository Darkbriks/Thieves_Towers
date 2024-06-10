#include "CardHand/DragAndDropCardVisualisation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tower.h"

ADragAndDropCardVisualisation::ADragAndDropCardVisualisation()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetMobility(EComponentMobility::Movable);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void ADragAndDropCardVisualisation::BeginPlay()
{
	Super::BeginPlay();
}

void ADragAndDropCardVisualisation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			if (HitResult.GetActor()->ActorHasTag("Floor") && HitResult.Normal.Z >= 0.9f)
			{
				bCanSpawn = true;
				SetActorLocation(HitResult.ImpactPoint);
				return;
			}
		}
	}
	bCanSpawn = false;
	this->SetActorLocation(FVector(0.0f, 0.0f, -500.0f));
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