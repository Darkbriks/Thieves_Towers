#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "SpawnTowerEffect.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class APrimitiveTower;

UCLASS()
class THIEVESTOWERS_API ASpawnTowerEffect : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY()
	TArray<AActor*> OverlappingObstacles;

public:
	ASpawnTowerEffect();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
