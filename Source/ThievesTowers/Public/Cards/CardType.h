#pragma once

#include "CoreMinimal.h"
#include "CardType.generated.h"

UENUM(Blueprintable)
enum ECardType
{
    TOWER UMETA(DisplayName = "Tower"),
    SPELL UMETA(DisplayName = "Spell"),
    MISCELLANEOUS UMETA(DisplayName = "Miscellaneous"),
    TELETOWERTATION UMETA(DisplayName = "Teletowertation")
};