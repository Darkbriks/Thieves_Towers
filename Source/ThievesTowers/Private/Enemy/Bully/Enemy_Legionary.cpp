#include "Enemy/Bully/Enemy_Legionary.h"
#include "Manager/GA_ThievesTowers.h"

void AEnemy_Legionary::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Si il y a au moins un autre legionnaire dans la range, on réduit les dégâts
	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		if (GameInstance->GetNumberEnemiesOfTypeInRange(AEnemy_Legionary::GetClass(), this->GetActorLocation(), Range) > 1)
		{
			for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage)
			{
				if (TypesOfDamageToReduce.Contains(TypeOfDamage))
				{
					DamageAmount -= DamageReduction;
					break;
				}
			}
		}
	}

	AEnemy::TakeDamage(DamageAmount, TypesOfDamage, DamageEvent, EventInstigator, DamageCauser);
}
