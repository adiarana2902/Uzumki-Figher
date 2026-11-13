#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UFCombatTypes.h"
#include "UFCharacter.generated.h"

class UUFWeaponComponent;
class UUFRewindComponent;

UCLASS(Blueprintable)
class UZUMAKIFIGHTER_API AUFCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AUFCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character|Health",
        meta=(ClampMin="1.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly, Category="Character|Health")
    float Health = 100.0f;

    UFUNCTION(BlueprintPure, Category="Character|Health")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintPure, Category="Character|Health")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintPure, Category="Character|Health")
    float GetHealthPercentage() const;

    UPROPERTY(ReplicatedUsing=OnRep_Team, BlueprintReadOnly, Category="Character|Team")
    EUFTeam Team = EUFTeam::None;

    UFUNCTION(BlueprintPure, Category="Character|Team")
    EUFTeam GetTeam() const { return Team; }

    UFUNCTION(BlueprintCallable, Category="Character|Team")
    void SetTeamAuthority(EUFTeam NewTeam);

    UPROPERTY(ReplicatedUsing=OnRep_Eliminated, BlueprintReadOnly, Category="Character|Combat")
    bool bIsEliminated = false;

    UFUNCTION(BlueprintPure, Category="Character|Combat")
    bool IsEliminated() const { return bIsEliminated; }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character|Combat")
    TObjectPtr<UUFWeaponComponent> WeaponComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character|Combat")
    TObjectPtr<UUFRewindComponent> RewindComponent;

    UFUNCTION(BlueprintCallable, Category="Character|Combat")
    float ApplyAuthoritativeDamage(float DamageAmount,
        AController* DamageInstigator, AActor* DamageCauser);

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
        AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category="Character|Combat")
    bool CanReceiveCombatDamage() const;

    UFUNCTION(BlueprintImplementableEvent, Category="Character|Health")
    void OnHealthChanged(float NewHealth, float AppliedDamage);

    UFUNCTION(BlueprintImplementableEvent, Category="Character|Combat")
    void OnCharacterEliminated(AController* EliminatingController, AActor* DamageCauser);

protected:
    UFUNCTION()
    void OnRep_Health(float PreviousHealth);

    UFUNCTION()
    void OnRep_Team();

    UFUNCTION()
    void OnRep_Eliminated();

    void HandleElimination(AController* EliminatingController, AActor* DamageCauser);

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
