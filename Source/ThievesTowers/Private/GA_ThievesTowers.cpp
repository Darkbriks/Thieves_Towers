#include "GA_ThievesTowers.h"
#include "ProjectileEffect/ProjectileEffect.h"
#include "Card.h"
#include "Containers/Ticker.h"

/*void UGA_ThievesTowers::Init()
{
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGA_ThievesTowers::Tick));
	Super::Init();
}

void UGA_ThievesTowers::Shutdown()
{
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
	Super::Shutdown();
}*/

void UGA_ThievesTowers::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("UGA_ThievesTowers::Tick"));
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