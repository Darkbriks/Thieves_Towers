#pragma once

#include "CoreMinimal.h"
#include "TypeOfDamage.generated.h"

UENUM(Blueprintable)
enum ETypeOfDamage
{
	Physical,
	Magical,
	Explosive,
};