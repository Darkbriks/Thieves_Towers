#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PrimitiveTowerWidget.generated.h"

class APrimitiveTower;
class UTargetingMode;
class UTextBlock;
class UButton;

UCLASS()
class THIEVESTOWERS_API UPrimitiveTowerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TowerName;

	UPROPERTY()
	APrimitiveTower* PrimitiveTower;

	virtual void NativeConstruct() override;

public:
	virtual void SetTower(APrimitiveTower* InTower);
};
