#include "ProjectileEffect/SimpleDamageEffect.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"

void USimpleDamageEffect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy)
{
	if (TargetEnemy)
	{
		TargetEnemy->TakeDamage(Damage, DamageTypes, FDamageEvent(), nullptr, nullptr);
	}
}