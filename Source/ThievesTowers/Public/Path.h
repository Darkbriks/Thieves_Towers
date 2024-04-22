#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

class USplineComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIEVESTOWERS_API APath : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	int SplinePointCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	FVector EndPoint = FVector(100, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APath* NextPath = nullptr;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Path")
	void UpdateSpline();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Path")
	void SetEndPointLocation();

	virtual void BeginPlay() override;
	
public:	
	APath();

	USplineComponent* GetSplineComponent() const { return SplineComponent; }
	APath* GetNextPath() const { return NextPath; }
};