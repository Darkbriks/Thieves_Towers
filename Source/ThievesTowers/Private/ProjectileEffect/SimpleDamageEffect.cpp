#include "ProjectileEffect/SimpleDamageEffect.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"

void USimpleDamageEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage)
{
	TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
	NewDamageTypes.Append(AdditionalTypesOfDamage);
	
	if (TargetEnemy)
	{
		TargetEnemy->TakeDamage(Damage, NewDamageTypes, FDamageEvent(), nullptr, nullptr);
	}
}