#include "Combat/Rewind/UFRewindComponent.h"

UUFRewindComponent::UUFRewindComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UUFRewindComponent::BeginPlay()
{
    Super::BeginPlay();
}
