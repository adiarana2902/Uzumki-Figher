#include "Characters/UFCharacter.h"

#include "Combat/Weapons/UFWeaponComponent.h"
#include "Combat/Rewind/UFRewindComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AUFCharacter::AUFCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);

    NetUpdateFrequency = 66.0f;
    MinNetUpdateFrequency = 33.0f;
    NetPriority = 3.0f;

    Health = MaxHealth;
    Team = EUFTeam::None;
    bIsEliminated = false;

    WeaponComponent = CreateDefaultSubobject<UUFWeaponComponent>(TEXT("WeaponComponent"));
    RewindComponent = CreateDefaultSubobject<UUFRewindComponent>(TEXT("RewindComponent"));

    GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Exponential;
}

void AUFCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        Health = FMath::Clamp(Health, 0.0f, MaxHealth);
    }
}

float AUFCharacter::GetHealthPercentage() const
{
    return MaxHealth > 0.0f ? FMath::Clamp(Health / MaxHealth, 0.0f, 1.0f) : 0.0f;
}

void AUFCharacter::SetTeamAuthority(EUFTeam NewTeam)
{
    if (!HasAuthority())
    {
        return;
    }

    Team = NewTeam;
    ForceNetUpdate();
}

bool AUFCharacter::CanReceiveCombatDamage() const
{
    return !bIsEliminated && Health > 0.0f;
}

float AUFCharacter::ApplyAuthoritativeDamage(
    float DamageAmount, AController* DamageInstigator, AActor* DamageCauser)
{
    if (!HasAuthority() || !CanReceiveCombatDamage() || DamageAmount <= 0.0f)
    {
        return 0.0f;
    }

    const float PreviousHealth = Health;
    Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
    const float AppliedDamage = PreviousHealth - Health;

    if (AppliedDamage <= 0.0f)
    {
        return 0.0f;
    }

    OnHealthChanged(Health, AppliedDamage);

    if (Health <= 0.0f)
    {
        HandleElimination(DamageInstigator, DamageCauser);
    }

    ForceNetUpdate();
    return AppliedDamage;
}

float AUFCharacter::TakeDamage(
    float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    if (!HasAuthority())
    {
        return 0.0f;
    }

    return ApplyAuthoritativeDamage(DamageAmount, EventInstigator, DamageCauser);
}

void AUFCharacter::HandleElimination(
    AController* EliminatingController, AActor* DamageCauser)
{
    if (!HasAuthority() || bIsEliminated)
    {
        return;
    }

    bIsEliminated = true;

    if (UCharacterMovementComponent* Movement = GetCharacterMovement())
    {
        Movement->StopMovementImmediately();
        Movement->DisableMovement();
    }

    OnCharacterEliminated(EliminatingController, DamageCauser);
    ForceNetUpdate();
}

void AUFCharacter::OnRep_Health(float PreviousHealth)
{
    OnHealthChanged(Health, FMath::Max(0.0f, PreviousHealth - Health));
}

void AUFCharacter::OnRep_Team()
{
}

void AUFCharacter::OnRep_Eliminated()
{
    if (bIsEliminated)
    {
        if (UCharacterMovementComponent* Movement = GetCharacterMovement())
        {
            Movement->DisableMovement();
        }
    }
}

void AUFCharacter::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AUFCharacter, Health);
    DOREPLIFETIME(AUFCharacter, Team);
    DOREPLIFETIME(AUFCharacter, bIsEliminated);
}
