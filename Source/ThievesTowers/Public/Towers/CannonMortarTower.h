#pragma once

#include "CoreMinimal.h"
#include "Towers/Tower.h"
#include "CannonMortarTower.generated.h"

UCLASS()
class THIEVESTOWERS_API ACannonMortarTower : public ATower
{
	GENERATED_BODY()

	ACannonMortarTower();

protected:
	virtual bool Attack() override;
};
