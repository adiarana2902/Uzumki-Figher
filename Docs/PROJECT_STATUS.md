# Project Status

## Target

- Unreal Engine 5.6
- Windows 64-bit
- C++ runtime module: UzumakiFighter
- Intended match size: 6v6 dedicated server

## Included in this repository

- UE 5.6 project descriptor and Game/Editor targets
- Runtime module entry point and Build.cs
- Replicated AUFCharacter baseline with team, health, and elimination state
- Weapon and rewind actor-component integration scaffolds
- Initial networking configuration and Git ignore rules

## Not yet implemented

The weapon and rewind components in this repository are deliberately minimal scaffolds. They do not yet implement firing, recoil, ammo, reload, rewind history, lag compensation, prediction reconciliation, or damage validation.

The separately generated UFCombat archive discussed in the project conversation has not been imported into this repository. No Unreal build, automation test, dedicated-server test, or 12-client validation has been run.

## Next engineering milestones

1. Implement data-driven weapon definitions and server-authoritative weapon runtime.
2. Add fire/reload RPC validation, sequence handling, and prediction acknowledgements.
3. Implement bounded server-side character hitbox history and rewind trace restoration.
4. Define dynamic cover occlusion semantics.
5. Add functional tests and network emulation test cases.
6. Compile in the user's UE 5.6 installation and resolve all compiler/integration errors.
