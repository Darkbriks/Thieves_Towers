#include "Projectiles/Effects/AOE_Effect.h"
#include "Manager/GA_ThievesTowers.h"
#include "Enemy/Enemy.h"
#include "Struct/AreaDamage.h"
#include "Engine/DamageEvents.h"
#include "DamageArea.h"

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

		if (bSpawnDamageArea && DamageAreaClass)
		{
			//GetWorld()->SpawnActor<ADamageArea>(DamageAreaClass, Transform.GetLocation(), FRotator::ZeroRotator);
			FVector Location = Transform.GetLocation();
			Location.Z = DamageAreaHeight;
			ADamageArea* DamageArea = GetWorld()->SpawnActor<ADamageArea>(DamageAreaClass, Location, FRotator::ZeroRotator);
			if (!DamageArea) { UE_LOG(LogTemp, Error, TEXT("Error spawning DamageArea")); return; }
		}
	}
}
