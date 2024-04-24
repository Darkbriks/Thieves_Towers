#include "Card.h"
#include "PaperSpriteComponent.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Movable);
	RootComponent = Root;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(Root);
}

void ACard::BeginPlay()
{
	Super::BeginPlay();
}

void ACard::OnHovered(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Hovered over card"));
}

void ACard::OnUnhovered(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Unhovered over card"));
}