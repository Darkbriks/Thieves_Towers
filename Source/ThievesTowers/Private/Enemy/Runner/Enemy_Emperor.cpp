#include "Enemy/Runner/Enemy_Emperor.h"

#include "GA_ThievesTowers.h"

void AEnemy_Emperor::Buff(AEnemy* Enemy)
{
	Enemy->SetMaxLife(Enemy->GetStartLife() + MaxLifeBuff);
	Enemy->SetLife(Enemy->GetLife() + MaxLifeBuff);
}

void AEnemy_Emperor::Unbuff(AEnemy* Enemy)
{
	Enemy->SetMaxLife(Enemy->GetStartLife());
	Enemy->SetLife(Enemy->GetLife() - MaxLifeBuff);
}

void AEnemy_Emperor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<AEnemy*> EnemiesToBuff;

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		for (AEnemy* Enemy : GameInstance->GetEnemies())
		{
			if (Enemy->GetClass() == ClassToBuff && FVector::Dist(GetActorLocation(), Enemy->GetActorLocation()) <= Range)
			{
				EnemiesToBuff.Add(Enemy);
			}
		}

		for (AEnemy* Enemy : EnemiesToBuff)
		{
			if (BuffedEnemies.Contains(Enemy)) { continue; }
			BuffedEnemies.Add(Enemy);
			Buff(Enemy);
		}

		for (int i = BuffedEnemies.Num() - 1; i >= 0; i--)
		{
			if (IsValid(BuffedEnemies[i]))
			{
				if (!EnemiesToBuff.Contains(BuffedEnemies[i]))
				{
					Unbuff(BuffedEnemies[i]);
					BuffedEnemies.RemoveAt(i);
				}
			}
		}
	}
}
