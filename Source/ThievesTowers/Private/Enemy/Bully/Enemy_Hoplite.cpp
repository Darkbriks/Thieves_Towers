#include "Enemy/Bully/Enemy_Hoplite.h"
#include "GA_ThievesTowers.h"

void AEnemy_Hoplite::InitializeEnemy(APath* NewPath, float NewCurrentDistance)
{
	Super::InitializeEnemy(NewPath, NewCurrentDistance);

	this->InitialSpeed = this->Speed;
}

void AEnemy_Hoplite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UGA_ThievesTowers* GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance()))
	{
		for (AEnemy* Enemy : GameInstance->GetEnemies())
		{
			if (AEnemy_Hoplite* Hoplite = Cast<AEnemy_Hoplite>(Enemy))
			{
				if (Hoplite != this && FVector::Dist(Hoplite->GetActorLocation(), GetActorLocation()) <= Range)
				{
					if (!HoplitesInRange.Contains(Hoplite))
					{
						HoplitesInRange.Add(Hoplite);
						this->SetLifeOverflows(this->GetLifeOverflows() + LifeGain);
					}
				}
				else if (HoplitesInRange.Contains(Hoplite))
				{
					HoplitesInRange.Remove(Hoplite);
					this->SetLifeOverflows(FMath::Max(0, this->GetLifeOverflows() - LifeGain));
				}
			}
		}
	}

	for (AEnemy_Hoplite* Hoplite : HoplitesInRange)
	{
		// Si un Hoplite est mort, on le retire de la liste
		if (!IsValid(Hoplite))
		{
			HoplitesInRange.Remove(Hoplite);
			this->SetLifeOverflows(FMath::Max(0, this->GetLifeOverflows() - LifeGain));
		}
	}

	this->Speed = FMath::Max(MinSpeed, InitialSpeed - LooseSpeed * HoplitesInRange.Num());
}