#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UFRewindComponent.generated.h"

/**
 * AUFCharacter-owned server rewind integration point.
 * Historical hitbox capture, bounded timestamp lookup, interpolation,
 * collision restoration, and lag-compensated traces are not implemented
 * in this scaffold.
 */
UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class UZUMAKIFIGHTER_API UUFRewindComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUFRewindComponent();

protected:
    virtual void BeginPlay() override;
};
