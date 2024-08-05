#include "Projectiles/Effects/LightningEffect.h"
#include "Projectiles/Effects/ProjectileEffect.h"
#include "Projectiles/Effects/Helpers/LightningHelper.h"

void ULightningEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage)
{
	TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
	NewDamageTypes.Append(AdditionalTypesOfDamage);
	
	if (ALightningHelper* Lightning = GetWorld()->SpawnActor<ALightningHelper>())
	{
		Lightning->InitializeLightning(TargetEnemy, NumberOfTargets, Damage, Range, NewDamageTypes, LightningColor, FreezeTime, TimeBetweenTargets);
	}
}
