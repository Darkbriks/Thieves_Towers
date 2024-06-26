#include "ProjectileEffect/AOE_Effect.h"
#include "GA_ThievesTowers.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"

void UAOE_Effect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy)
{
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetWorld()->GetGameInstance()))
	{
		TArray<AEnemy*> Enemies = GameInstance->GetEnemies();
		for (AEnemy* Enemy : Enemies)
		{
			float Distance = FVector::Dist(Enemy->GetActorLocation(), Transform.GetLocation());
			for (FAOE_Params Params : AOE_Params)
			{
				if (Distance <= Params.Radius)
				{
					Enemy->TakeDamage(Params.Damage, DamageTypes, FDamageEvent(), nullptr, nullptr);
					break;
				}
			}
		}
	}
}
