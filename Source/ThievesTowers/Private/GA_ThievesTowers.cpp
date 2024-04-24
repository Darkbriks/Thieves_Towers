#include "GA_ThievesTowers.h"
#include "ProjectileEffect/ProjectileEffect.h"

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