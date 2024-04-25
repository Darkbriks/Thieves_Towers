#include "GA_ThievesTowers.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Card.h"
#include "Tower.h"
#include "Enemy/Little/Enemy_Silly.h"

void UGA_ThievesTowers::Tick(float DeltaTime)
{
	TArray<ATower*> TowersToDesactivate;
	for (AEnemy* Enemy : Enemies)
	{
		if (AEnemy_Silly* SillyEnemy = Cast<AEnemy_Silly>(Enemy))
		{
			for (ATower* Tower : Towers)
			{
				if (FVector::Dist(SillyEnemy->GetActorLocation(), Tower->GetActorLocation()) <= SillyEnemy->GetRange())
				{
					TowersToDesactivate.Add(Tower);
				}
			}
		}
	}

	for (ATower* Tower : Towers)
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

void UGA_ThievesTowers::AddCardToHand(TSubclassOf<ACard> CardClass)
{
	if (Hand.Num() >= MaxHandSize) { return; }
	Hand.Add(CardClass);
	
	if (CreateHandDelegate.ExecuteIfBound(Hand)) { UE_LOG(LogTemp, Warning, TEXT("CreateHandDelegate executed")); }
	else { UE_LOG(LogTemp, Warning, TEXT("CreateHandDelegate not executed")); }
}

void UGA_ThievesTowers::RemoveCardFromHand(TSubclassOf<ACard> CardClass)
{
	for (int i = 0; i < Hand.Num(); i++) { if (Hand[i] == CardClass) { Hand.RemoveAt(i); break; } }
	
	if (CreateHandDelegate.ExecuteIfBound(Hand)) { UE_LOG(LogTemp, Warning, TEXT("CreateHandDelegate executed")); }
	else { UE_LOG(LogTemp, Warning, TEXT("CreateHandDelegate not executed")); }
}

void UGA_ThievesTowers::AddTower(ATower* Tower) { Towers.Add(Tower); }
void UGA_ThievesTowers::RemoveTower(ATower* Tower) { Towers.Remove(Tower); }
void UGA_ThievesTowers::AddEnemy(AEnemy* Enemy) { Enemies.Add(Enemy); }
void UGA_ThievesTowers::RemoveEnemy(AEnemy* Enemy) { Enemies.Remove(Enemy); }