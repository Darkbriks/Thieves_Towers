#pragma once

#include "CoreMinimal.h"
#include "PrimitiveTower.h"
#include "GameFramework/Actor.h"
#include "Capacitour.generated.h"

UCLASS()
class THIEVESTOWERS_API ACapacitour : public APrimitiveTower
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower - Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BasementMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower - Attributes")
	TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage = { Physical, Magical, Explosive };
	
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	ACapacitour();
};
