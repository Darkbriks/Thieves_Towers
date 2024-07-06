#include "ProjectileEffect/AOE_Effect.h"
#include "GA_ThievesTowers.h"
#include "Enemy/Enemy.h"
#include "Struct/AreaDamage.h"
#include "Engine/DamageEvents.h"

void UAOE_Effect::ApplyEffect(FTransform Transform, AEnemy* TargetEnemy, TArray<TEnumAsByte<ETypeOfDamage>> AdditionalTypesOfDamage)
{
	TArray<TEnumAsByte<ETypeOfDamage>> NewDamageTypes = DamageTypes;
	NewDamageTypes.Append(AdditionalTypesOfDamage);
	
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetWorld()->GetGameInstance()))
	{
		TArray<AEnemy*> Enemies = GameInstance->GetEnemies();
		for (AEnemy* Enemy : Enemies)
		{
			float Distance = FVector::Dist(Enemy->GetActorLocation(), Transform.GetLocation());
			for (FAreaDamage Params : AOE_Params)
			{
				if (Distance <= Params.Radius)
				{
					Enemy->TakeDamage(Params.Damage, NewDamageTypes, FDamageEvent(), nullptr, nullptr);
					break;
				}
			}
		}
	}
}
