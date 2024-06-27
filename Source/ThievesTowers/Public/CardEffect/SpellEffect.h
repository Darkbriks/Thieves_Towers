#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "SpellEffect.generated.h"

class UCapsuleComponent;
class AEnemy;
class UNiagaraSystem;
enum ETypeOfDamage : int;

UCLASS()
class THIEVESTOWERS_API ASpellEffect : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float Range = 500.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	FTransform ParticleSystemTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float TimeBeforeDamage = 1.0f;

public:
	ASpellEffect();
	
	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyEffect() override;
};
