#include "Combat/Weapons/UFWeaponComponent.h"

UUFWeaponComponent::UUFWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UUFWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}
