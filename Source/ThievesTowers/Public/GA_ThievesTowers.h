#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GA_ThievesTowers.generated.h"

class UProjectileEffect;

UCLASS()
class THIEVESTOWERS_API UGA_ThievesTowers : public UGameInstance
{
	GENERATED_BODY()

	TArray<UProjectileEffect*> ProjectileEffects;

public:
	UProjectileEffect* GetProjectileEffect(TSubclassOf<UProjectileEffect> EffectClass);
};