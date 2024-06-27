#pragma once

#include "CoreMinimal.h"
#include "Enum/TypeOfDamage.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "AOE_Effect.generated.h"

struct FAreaDamage;

UCLASS()
class THIEVESTOWERS_API UAOE_Effect : public UProjectileEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect", meta=(ToolTip="Warning: The first element of this array will be the center of the AOE"))
	TArray<FAreaDamage> AOE_Params;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes;

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy) override;
};
