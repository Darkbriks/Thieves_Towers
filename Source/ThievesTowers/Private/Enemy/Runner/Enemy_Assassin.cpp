#include "Enemy/Runner/Enemy_Assassin.h"
#include "PaperSpriteComponent.h"

void AEnemy_Assassin::Camouflage()
{
	bCanCamouflage = false;
	bCanBeTargeted = false;
	bIsCamouflaged = true;
	DynamicMaterial->SetScalarParameterValue(FName("Alpha"), 0.5f);
	DynamicMaterial->SetVectorParameterValue(FName("Color"), CamouflageColor);
	CamouflageTimeRemaining = CamouflageTime;
}

void AEnemy_Assassin::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AEnemy::TakeDamage(DamageAmount, TypesOfDamage, DamageEvent, EventInstigator, DamageCauser);
	if (GetLife() <= 0.0f || !bCanCamouflage) { return; }

	for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage) { if (CamouflageTypesOfDamage.Contains(TypeOfDamage)) { Camouflage(); return; } }
}

void AEnemy_Assassin::Tick(float DeltaTime)
{
	AEnemy::Tick(DeltaTime);

	if (bIsCamouflaged)
	{
		CamouflageTimeRemaining -= DeltaTime;
		if (CamouflageTimeRemaining <= 0.0f)
		{
			bIsCamouflaged = false;
			bCanBeTargeted = true;
			DynamicMaterial->SetScalarParameterValue(FName("Alpha"), 1.0f);
			GetSpriteComponent()->SetSprite(AfterCamouflageSprite);
		}
	}
}