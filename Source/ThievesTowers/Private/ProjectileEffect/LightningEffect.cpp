#include "ProjectileEffect/LightningEffect.h"
#include "ProjectileEffect/Headers/LightningHeader.h"

void ULightningEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy)
{
	if (ALightningHeader* Lightning = GetWorld()->SpawnActor<ALightningHeader>())
	{
		Lightning->InitializeLightning(TargetEnemy, NumberOfTargets, Damage, Range, TypeOfDamage, LightningColor, FreezeTime, TimeBetweenTargets);
	}
}
