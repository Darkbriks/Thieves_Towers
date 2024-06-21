#include "CardEffect/CardEffect.h"

ACardEffect::ACardEffect()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetMobility(EComponentMobility::Movable);
}

bool ACardEffect::ApplyEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("ACardEffect::ApplyEffect() called"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ACardEffect::ApplyEffect() called"));
	Destroy(); return true;
}

void ACardEffect::CancelEffect()
{
	Destroy();
}