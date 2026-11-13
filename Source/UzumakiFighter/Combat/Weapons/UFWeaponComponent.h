#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UFWeaponComponent.generated.h"

/**
 * AUFCharacter-owned weapon component integration point.
 * Weapon runtime, RPC validation, ammo/reload state, recoil prediction,
 * and authoritative hit resolution are not implemented in this scaffold.
 */
UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class UZUMAKIFIGHTER_API UUFWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUFWeaponComponent();

protected:
    virtual void BeginPlay() override;
};
