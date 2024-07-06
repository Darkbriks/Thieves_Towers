#include "ProjectileEffect/LightningEffect.h"
#include "ProjectileEffect/Headers/LightningHeader.h"

void ULightningEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage)
{
	TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
	NewDamageTypes.Append(AdditionalTypesOfDamage);
	
	if (ALightningHeader* Lightning = GetWorld()->SpawnActor<ALightningHeader>())
	{
		Lightning->InitializeLightning(TargetEnemy, NumberOfTargets, Damage, Range, NewDamageTypes, LightningColor, FreezeTime, TimeBetweenTargets);
	}
}
