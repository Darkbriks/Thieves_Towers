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
	virtual void ApplyEffect()
	{
		UE_LOG(LogTemp, Warning, TEXT("Applying effect %s"), *EffectName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Applying effect %s"), *EffectName.ToString()));
	}
};