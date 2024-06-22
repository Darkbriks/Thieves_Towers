#pragma once

#include "CoreMinimal.h"
#include "CardEffect/CardEffect.h"
#include "SpellEffect.generated.h"

class UCapsuleComponent;
class AEnemy;
enum ETypeOfDamage : int;

UCLASS()
class THIEVESTOWERS_API ASpellEffect : public ACardEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<ETypeOfDamage>> TypesOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UParticleSystem> ParticleSystem;

	UPROPERTY()
	TArray<AEnemy*> OverlappingEnemies;

public:
	ASpellEffect();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Tick(float DeltaTime) override;
	virtual bool ApplyEffect() override;
};
