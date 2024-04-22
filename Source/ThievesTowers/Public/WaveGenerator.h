#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveGenerator.generated.h"

class APath;
struct FWaveParams;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIEVESTOWERS_API AWaveGenerator : public AActor
{
	GENERATED_BODY()

	// Variables
	float TimeSinceLastSpawn = 0.0f;
	int CurrentEnemyIndex = 0;
	int CurrentEnemyCount = 0;
	FVector SpawnLocation;
	FRotator SpawnRotation;

protected:
	// Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Generator")
	TArray<FWaveParams> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Generator")
	APath* StartPath;

	// Methods
	void SpawnEnemy();

	// Overridden methods
	virtual void BeginPlay() override;

public:
	// Constructors
	AWaveGenerator();

	// Overridden methods
	virtual void Tick(float DeltaTime) override;
};