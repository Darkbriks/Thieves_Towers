#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardEffect.generated.h"

UCLASS(Blueprintable)
class THIEVESTOWERS_API ACardEffect : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	
	bool bCanApplyEffect = false;
	
public:
	ACardEffect();

	virtual bool ApplyEffect();
	virtual void CancelEffect();
};