#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "SpellEffect.generated.h"

class UProjectileEffect;
class UCapsuleComponent;
class AEnemy;
class UNiagaraSystem;

UCLASS()
class THIEVESTOWERS_API ASpellEffect : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UProjectileEffect> Effect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	FTransform ParticleSystemTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float TimeBeforeDamage = 1.0f;

public:
	ASpellEffect();
	
	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyEffect(FCardInfo CardInfo) override;
};
