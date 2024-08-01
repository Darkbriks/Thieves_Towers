#include "WaveGenerator.h"
#include "Manager/GA_ThievesTowers.h"
#include "Enemy/Enemy.h"
#include "Path.h"
#include "Components/SplineComponent.h"
#include "Struct/WaveParams.h"

//////////////////////////////////////////////////////////////////////////
/// UWaveGenerator - Constructor
//////////////////////////////////////////////////////////////////////////
AWaveGenerator::AWaveGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	this->StartPath = nullptr;
}

//////////////////////////////////////////////////////////////////////////
/// UWaveGenerator - Protected Methods
//////////////////////////////////////////////////////////////////////////
void AWaveGenerator::SpawnEnemy()
{
	AEnemy* NewEnemy = GetWorld()->SpawnActor<AEnemy>(Waves[CurrentEnemyIndex].EnemyClass, SpawnLocation, SpawnRotation);
	NewEnemy->InitializeEnemy(StartPath);
	CurrentEnemyCount++;

	if (CurrentEnemyCount >= Waves[CurrentEnemyIndex].EnemyCount)
	{
		CurrentEnemyIndex++; CurrentEnemyCount = 0;
		if (CurrentEnemyIndex >= Waves.Num())
		{
			if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetWorld()->GetGameInstance()))
			{
				GameInstance->GetMapManager()->RemoveWave(this);
			}
			Destroy();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
/// UWaveGenerator - Overridden Methods - UActorComponent
//////////////////////////////////////////////////////////////////////////
void AWaveGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (Waves.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No enemy settings found. Destroying actor."));
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("No enemy settings found. Destroying actor."));
		Destroy(); return;
	}

	if (!StartPath)
	{
		UE_LOG(LogTemp, Warning, TEXT("No start path found. Destroying actor."));
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("No start path found. Destroying actor."));
		Destroy();  return;
	}

	for (FWaveParams Wave : Waves)
	{
		if (!Wave.EnemyClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy class  at index %d is null. Destroying actor."), CurrentEnemyIndex);
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("Enemy class at index %d is null. Destroying actor."), CurrentEnemyIndex));
			Destroy();  return;
		}
	}

	SpawnLocation = StartPath->GetSplineComponent()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	SpawnRotation = StartPath->GetSplineComponent()->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);
}

//////////////////////////////////////////////////////////////////////////
/// UWaveGenerator - Overridden Methods - UActorComponent
//////////////////////////////////////////////////////////////////////////
void AWaveGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsStarted) { return; }

	if (CurrentEnemyCount == 0)
	{
		TimeSinceLastSpawn += DeltaTime;
		if (TimeSinceLastSpawn >= Waves[CurrentEnemyIndex].TimeBeforeFirstSpawn)
		{
			TimeSinceLastSpawn -= Waves[CurrentEnemyIndex].TimeBeforeFirstSpawn;
			SpawnEnemy();
		}
		return;
	}

	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= Waves[CurrentEnemyIndex].SpawnRate)
	{
		TimeSinceLastSpawn -= Waves[CurrentEnemyIndex].SpawnRate;
		SpawnEnemy();
	}
}

