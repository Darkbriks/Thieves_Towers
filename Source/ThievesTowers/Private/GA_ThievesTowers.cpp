#include "GA_ThievesTowers.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Towers/PrimitiveTower.h"
#include "Enemy/Little/Enemy_Silly.h"

//////////////////////////////////////////////////////////////////////////
/// UGA_ThievesTowers - Tick
//////////////////////////////////////////////////////////////////////////
void UGA_ThievesTowers::Tick(float DeltaTime)
{
	TArray<APrimitiveTower*> TowersToDesactivate;
	for (AEnemy* Enemy : Enemies)
	{
		if (AEnemy_Silly* SillyEnemy = Cast<AEnemy_Silly>(Enemy))
		{
			for (APrimitiveTower* Tower : Towers)
			{
				if (FVector::Dist(SillyEnemy->GetActorLocation(), Tower->GetActorLocation()) <= SillyEnemy->GetRange())
				{
					TowersToDesactivate.Add(Tower);
				}
			}
		}
	}

	for (APrimitiveTower* Tower : Towers)
	{
		if (TowersToDesactivate.Contains(Tower)) { Tower->Deactivate(); }
		else { Tower->Activate(); }
	}
}

UProjectileEffect* UGA_ThievesTowers::GetProjectileEffect(TSubclassOf<UProjectileEffect> EffectClass)
{
	for (UProjectileEffect* Effect : ProjectileEffects)
	{
		if (Effect->GetClass() == EffectClass) { return Effect; } // Return the effect if it already exists
	}

	// Else, create a new effect
	UProjectileEffect* NewEffect = NewObject<UProjectileEffect>(this, EffectClass);
	ProjectileEffects.Add(NewEffect);
	return NewEffect;
}

int UGA_ThievesTowers::GetNumberEnemiesOfType(TSubclassOf<AEnemy> EnemyClass)
{
	int NumberEnemies = 0;
	for (AEnemy* Enemy : Enemies) { if (Enemy->GetClass() == EnemyClass) { NumberEnemies++; } }
	return NumberEnemies;
}

int UGA_ThievesTowers::GetNumberEnemiesOfTypeInRange(TSubclassOf<AEnemy> EnemyClass, FVector Location, float Range)
{
	int NumberEnemies = 0;
	for (AEnemy* Enemy : Enemies) { if (Enemy->GetClass() == EnemyClass) { if (FVector::Dist(Location, Enemy->GetActorLocation()) <= Range) { NumberEnemies++; } } }
	return NumberEnemies;
}

void UGA_ThievesTowers::AddTower(APrimitiveTower* Tower) { Towers.Add(Tower); }
void UGA_ThievesTowers::RemoveTower(APrimitiveTower* Tower) { Towers.Remove(Tower); }
void UGA_ThievesTowers::AddEnemy(AEnemy* Enemy) { Enemies.Add(Enemy); }
void UGA_ThievesTowers::RemoveEnemy(AEnemy* Enemy) { Enemies.Remove(Enemy); if (Enemies.Num() == 0) { GetMapManager()->CheckEndRound(); } }