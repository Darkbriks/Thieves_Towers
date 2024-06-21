#include "CardEffect/SpawnTowerEffect.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Tower.h"

ASpawnTowerEffect::ASpawnTowerEffect()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetMobility(EComponentMobility::Movable);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Root);
	Sphere->SetSphereRadius(100.0f);
	Sphere->SetCollisionProfileName("OverlapAllDynamic");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTowerEffect::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASpawnTowerEffect::OnOverlapEnd);
	Sphere->SetMobility(EComponentMobility::Movable);

	OverlappingObstacles = TArray<AActor*>();
}

void ASpawnTowerEffect::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Obstacle") || OtherComp->ComponentHasTag("Tower-Basement"))
	{
		OverlappingObstacles.Add(OtherActor);
	}
}

void ASpawnTowerEffect::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Obstacle") || OtherComp->ComponentHasTag("Tower-Basement"))
	{
		OverlappingObstacles.Remove(OtherActor);
	}
}

void ASpawnTowerEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCanApplyEffect = false;

	FVector WorldPosition;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), UWidgetLayoutLibrary::GetMousePositionOnViewport(this) * UWidgetLayoutLibrary::GetViewportScale(this), WorldPosition, WorldDirection);

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(), WorldPosition, WorldPosition + WorldDirection * 10000.0f, ETraceTypeQuery::TraceTypeQuery1, false, { this }, EDrawDebugTrace::None, HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
	if (HitResults.Num() > 0)
	{
		for (FHitResult HitResult : HitResults)
		{
			SetActorLocation(HitResult.ImpactPoint);
			if (OverlappingObstacles.Num() == 0 && HitResult.GetActor()->ActorHasTag("Floor") && HitResult.Normal.Z >= 0.9f)
			{
				Mesh->SetRenderCustomDepth(false);
				bCanApplyEffect = true;
				return;
			}
		}
		Mesh->SetRenderCustomDepth(true);
		return;
	}
	this->SetActorLocation(WorldPosition + WorldDirection * 1000.0f);
}

bool ASpawnTowerEffect::ApplyEffect()
{
	if (TowerToSpawn && !bCanApplyEffect) { Destroy(); return false; }
	GetWorld()->SpawnActor<ATower>(TowerToSpawn, GetActorLocation(), FRotator::ZeroRotator);
	Destroy(); return true;
}