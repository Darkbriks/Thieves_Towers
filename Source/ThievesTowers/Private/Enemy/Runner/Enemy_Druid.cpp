#include "Enemy/Runner/Enemy_Druid.h"
#include "Manager/GA_ThievesTowers.h"

void AEnemy_Druid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HealCooldownTimer += DeltaTime;
	if (HealCooldownTimer >= HealCooldown)
	{
		HealCooldownTimer -= HealCooldown;

		if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
		{
			for (AEnemy* Enemy : GameInstance->GetEnemies())
			{
				if (FVector::Dist(Enemy->GetActorLocation(), GetActorLocation()) <= HealRange)
				{
					Enemy->Heal(HealAmount);
					UE_LOG(LogTemp, Warning, TEXT("%s healed %s"), *GetName(), *Enemy->GetName());
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("%s healed %s"), *GetName(), *Enemy->GetName()));
				}
			}
		}
	}
}
