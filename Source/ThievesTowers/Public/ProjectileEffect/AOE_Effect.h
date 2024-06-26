#pragma once

#include "CoreMinimal.h"

#include "Enum/TypeOfDamage.h"

#include "ProjectileEffect/ProjectileEffect.h"
#include "AOE_Effect.generated.h"

USTRUCT(Blueprintable)
struct FAOE_Params
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect - Attributes")
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect - Attributes")
	int Damage = 1;
};

UCLASS()
class THIEVESTOWERS_API UAOE_Effect : public UProjectileEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect", meta=(ToolTip="Warning: The first element of this array will be the center of the AOE"))
	TArray<FAOE_Params> AOE_Params;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect")
	TArray<TEnumAsByte<ETypeOfDamage>> DamageTypes;

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy) override;
};
