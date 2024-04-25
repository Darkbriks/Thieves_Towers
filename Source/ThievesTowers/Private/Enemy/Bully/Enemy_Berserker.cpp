#include "Enemy/Bully/Enemy_Berserker.h"
#include "PaperSpriteComponent.h"

void AEnemy_Berserker::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bCanEnterInBersekerMode)
	{
		for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage)
		{
			if (BerserkerTypesOfDamage.Contains(TypeOfDamage))
			{
				bCanEnterInBersekerMode = false;
				Speed += BerserkerSpeedGain;
				DamageAmount += BerserkerLifeLoss;
				GetSpriteComponent()->SetSprite(BerserkerSprite);
				if (GetLife() - DamageAmount <= 0.0f) { DamageAmount = GetLife() - 1.0f; }
				break;
			}
		}
	}
	
	AEnemy::TakeDamage(DamageAmount, TypesOfDamage, DamageEvent, EventInstigator, DamageCauser);
}