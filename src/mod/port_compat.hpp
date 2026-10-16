#pragma once
// Windows GD 2.2074 compatibility policy.
//
// Upstream v0.3.2 was REVERSE-ENGINEERED against the GD 2.2081 executable.
// 2.2081's process-global RNG addresses (0x6c2e90 / 0x6c2ee0 / 0x6c2ef8)
// MUST NOT be read or written on 2.2074 without independently confirming
// their RVAs, type, and writable memory region on that *exact* GD build.
//
// This keeps the solver's DP, hooks, candidate verification and replay intact;
// the unsafe random-seed hack is OFF by default. Random-trigger levels cannot
// be promised deterministic retries while this compatibility mode is active.
//
// A future verified port may supply new measured addresses and re-enable it.
namespace p1::compat {
inline constexpr bool verifiedProcessRng = false;
inline constexpr char const* description =
    "GD 2.2074 conservative port: unverified 2.2081 RNG patching disabled";
}
