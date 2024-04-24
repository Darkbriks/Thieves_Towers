#pragma once

#include "CoreMinimal.h"
#include "CardEffect.generated.h"

UCLASS(Blueprintable)
class THIEVESTOWERS_API UCardEffect : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Effect")
	FName EffectName;
	
public:
	virtual void ApplyEffect() {}
};