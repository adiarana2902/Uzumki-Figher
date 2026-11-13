#pragma once

#include "CoreMinimal.h"
#include "UFCombatTypes.generated.h"

UENUM(BlueprintType)
enum class EUFTeam : uint8
{
    None  UMETA(DisplayName = "None"),
    Alpha UMETA(DisplayName = "Alpha"),
    Bravo UMETA(DisplayName = "Bravo")
};
