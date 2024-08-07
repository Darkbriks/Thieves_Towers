#include "Towers/PrimitiveTower.h"
#include "MainHUD.h"
#include "Manager/GA_ThievesTowers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

APrimitiveTower::APrimitiveTower()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SceneComponent->Mobility = EComponentMobility::Movable;
	RootComponent = SceneComponent;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleSize(Range, 5000.0f);
	CapsuleComponent->SetGenerateOverlapEvents(true);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName("OverlapAllDynamic");
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->ComponentTags.Add("Tower-Basement");
}

void APrimitiveTower::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->SetCapsuleRadius(Range);
	if (UGA_ThievesTowers *GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		GameInstance->AddTower(this);
		GameInstance->GetMapManager()->GetMainHUD()->TowerSelected(this);
	}
	Activate();
}

void APrimitiveTower::Destroyed()
{
	Super::Destroyed();
	if (UGA_ThievesTowers *GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		GameInstance->RemoveTower(this);
		GameInstance->GetMapManager()->GetMainHUD()->TowerDeselected(this);
	}
}

void APrimitiveTower::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void APrimitiveTower::Activate() { bIsActivated = true; }
void APrimitiveTower::Deactivate() { bIsActivated = false; }