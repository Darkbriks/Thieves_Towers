#include "Towers/CannonMortarTower.h"
#include "Towers/Targeting/MostHealtly.h"
#include "Projectile.h"

ACannonMortarTower::ACannonMortarTower()
{
	TargetingModeClass = UMostHealtly::StaticClass();
}

bool ACannonMortarTower::Attack()
{
	if (AEnemy* Enemy = GetEnemyInRange())
	{
		FVector ProjectileLocation = GetActorLocation();
		ProjectileLocation += GetActorForwardVector() * ProjectileXOffset;
		ProjectileLocation += GetActorRightVector() * ProjectileYOffset;
		ProjectileLocation += GetActorUpVector() * ProjectileZOffset;
		
		if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, FRotator::ZeroRotator))
		{
			Enemy->AddProjectile(Projectile);
			Projectile->InitializeProjectile(Enemy->GetActorLocation(), Enemy, AdditionalTypesOfDamage);
			Projectile->Launch();
			return true;
		}
	}
	return false;
}