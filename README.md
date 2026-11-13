# Uzumaki Fighter

Unreal Engine 5.6 multiplayer tactical action game foundation.

## Current source foundation

- Baseline replicated character class: `AUFCharacter`
- Team identity: `EUFTeam`
- Server-authoritative health and elimination interface
- Character component integration points for weapon and rewind systems
- Initial combat architecture and integration notes

## Engine target

- Unreal Engine 5.6
- Windows 64-bit development
- C++ gameplay module: `UzumakiFighter`
- Dedicated-server architecture planned for 6v6 matches

## Source layout

```
Source/UzumakiFighter/
  Characters/
    UFCombatTypes.h
    UFCharacter.h
    UFCharacter.cpp
  Combat/
    Weapons/
    Rewind/
  UzumakiFighter.Build.cs
```

## Important implementation status

This repository currently contains the baseline character source and integration documentation. The previously drafted UFCombat archive is a separate, unverified source foundation and has not yet been imported into this repository. No UE 5.6 compile or multiplayer test has been run.

Before treating this as a production build, integrate the weapon and rewind implementation, compile against the installed UE 5.6 toolchain, and run dedicated-server tests with simulated latency and packet loss.

## Integration contract

Combat code should use the following server-side character API:

- `GetTeam()`
- `CanReceiveCombatDamage()`
- `ApplyAuthoritativeDamage(float, AController*, AActor*)`
- `GetHealth()`
- `IsEliminated()`

Clients must never authoritatively select hit actors, damage amounts, hit locations, or headshot outcomes.
