#include "Enemy/Runner/Enemy_Teleporter.h"
#include "PaperSpriteComponent.h"

void AEnemy_Teleporter::StartFakeTeleport()
{
	bCanUseTeleport = false;
	StartDistance = CurrentPathDistance;
	Speed *= SpeedMultiplier;
	bIsTeleporting = true;
}

void AEnemy_Teleporter::EndFakeTeleport()
{
	Speed /= SpeedMultiplier;
	GetSpriteComponent()->SetSprite(AfterTeleportSprite);
	bIsTeleporting = false;
}

void AEnemy_Teleporter::TakeDamage(int DamageAmount, TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AEnemy::TakeDamage(DamageAmount, TypesOfDamage, DamageEvent, EventInstigator, DamageCauser);
	if (GetLife() <= 0.0f || !bCanUseTeleport) { return; }

	for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage) { if (TeleportTypesOfDamage.Contains(TypeOfDamage)) { StartFakeTeleport(); return; } }
}

void AEnemy_Teleporter::Tick(float DeltaTime)
{
	AEnemy::Tick(DeltaTime);
	if (bIsTeleporting && TraveledDistance - StartDistance >= TeleportDistance) { EndFakeTeleport(); }
}