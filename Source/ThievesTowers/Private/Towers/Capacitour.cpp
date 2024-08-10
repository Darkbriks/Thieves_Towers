#include "Towers/Capacitour.h"
#include "Components/CapsuleComponent.h"
#include "Manager/GA_ThievesTowers.h"
#include "Manager/MapManager.h"
#include "MainHUD.h"

ACapacitour::ACapacitour()
{
	BasementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasementMesh"));
	BasementMesh->SetupAttachment(RootComponent);
	BasementMesh->SetGenerateOverlapEvents(false);
	BasementMesh->OnClicked.AddDynamic(this, &ACapacitour::OnMouseButtonDown);

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACapacitour::BeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ACapacitour::EndOverlap);
}

void ACapacitour::OnMouseButtonDown(UPrimitiveComponent* PrimitiveComponent, FKey InKey)
{
	if (UGA_ThievesTowers *GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		GameInstance->GetMapManager()->GetMainHUD()->TowerSelected(this);
	}
}

void ACapacitour::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Tower-Basement"))
	{
		if (APrimitiveTower* Tower = Cast<APrimitiveTower>(OtherActor))
		{
			if (Tower->GetClass() == GetClass()) { return; }
			for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Adding %s damage to %s"), *UEnum::GetValueAsString(TypeOfDamage), *Tower->GetName()));
				Tower->AddAdditionalTypeOfDamage(TypeOfDamage);
			}
		}
	}
}

void ACapacitour::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("Tower-Basement"))
	{
		if (APrimitiveTower* Tower = Cast<APrimitiveTower>(OtherActor))
		{
			if (Tower->GetClass() == GetClass()) { return; }
			for (TEnumAsByte<ETypeOfDamage> TypeOfDamage : TypesOfDamage)
			{
				Tower->RemoveAdditionalTypeOfDamage(TypeOfDamage);
			}
		}
	}
}