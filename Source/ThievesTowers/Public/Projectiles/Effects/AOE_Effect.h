#pragma once

#include "CoreMinimal.h"
#include "Projectiles/TypeOfDamage.h"
#include "ProjectileEffect.h"
#include "AOE_Effect.generated.h"

class ADamageArea;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect")
	bool bSpawnDamageArea = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect", meta=(EditCondition="bSpawnDamageArea"))
	TSubclassOf<ADamageArea> DamageAreaClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AOE Effect", meta=(EditCondition="bSpawnDamageArea"))
	float DamageAreaHeight = 0.0f;

public:
	virtual void ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage) override;
};
