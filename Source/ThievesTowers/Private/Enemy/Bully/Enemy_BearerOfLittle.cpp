#include "Enemy/Bully/Enemy_BearerOfLittle.h"

void AEnemy_BearerOfLittle::SpawnEnemies()
{
	if (ClassToSpawn)
	{
		for (int i = 0; i < NumberOfEnemiesToSpawn; i++)
		{
			AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(ClassToSpawn, GetActorLocation(), FRotator::ZeroRotator);
			Enemy->InitializeEnemy(this->CurrentPath, this->CurrentPathDistance + (i % 2 * 2 - 1) * SpaceBetweenEnemies * i / 2);
		}
	}
}

void AEnemy_BearerOfLittle::Die()
{
	SpawnEnemies();
	Super::Die();
}
