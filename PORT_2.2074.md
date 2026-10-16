# GDSolver v0.3.2 / Geometry Dash 2.2074 — conservative repair pass

This is an updated **source** port, not a proven playable binary. The original
0.3.2 solver was calibrated on **Windows GD 2.2081**. Merely setting the
`mod.json` GD target to `2.2074` does not port binary offsets, hooks or physics.

## Changes made in this repair pass

1. **Unverified RNG addresses no longer get written on 2.2074.** The original
   mod read/wrote three process-global seeds at GD 2.2081 RVAs `0x6c2e90`,
   `0x6c2ee0`, `0x6c2ef8`. `compat::verifiedProcessRng` is false, and all
   accesses to these specific addresses are guarded. `rngfix` now defaults to
   off and `rngfresh`, `rngseed` and explicit `rngfix=1` cannot enable those
   writes. Random-trigger levels may now be nondeterministic, by design.
2. **Checkpoint cleanup uses GD's native `removeCheckpoint(false)`**, with a
   progress check, rather than dereferencing an unverified `GameObject+0x2f0`
   and manually releasing nodes. This may be slower, but avoids a particularly
   dangerous potential use-after-free/wrong-member access on 2.2074.
3. **Removed 2.2081-only member-offset `static_assert`s** from the play-menu.
   The named members provided by the actual target SDK are used instead.
4. The in-game random-level warning no longer claims that the seeds are fixed.
   A log message on load warns when operating in conservative compatibility mode.
5. Added an offline safety regression test and a core DP smoke-test CI job.

## Running checks without Geometry Dash

```sh
cmake -S . -B build-dp -DCMAKE_BUILD_TYPE=Release -DGDSOLVER_BUILD_MOD=OFF
cmake --build build-dp --target dptest
./build-dp/dp/dptest   # Linux; on Windows, build-dp\dp\Release\dptest.exe
python py/test_22074_safety.py
```

The core DP tests **passed** in a Linux C++ build while preparing this patch.
These tests do not compile or exercise the Geode DLL.

## Producing a Windows mod

Upload this repository to GitHub, then open **Actions → Build → Run workflow**.
The existing `windows` job fetches Geode SDK `v4.6.3` and attempts to build
`gdsolver.solver.geode`. If the workflow succeeds, find the output under its
`geode-package` artifact and copy the `.geode` file into your GD 2.2074
`geode/mods/` directory. The Windows workflow and DLL were NOT run/tested here:
there is no GD installation, Windows environment or Geode SDK in this container.

For a first test, avoid running multiple mods together, test **Normal** mode
before **Solve**, and keep a backup of game data. Please send the **first
compile error** (if CI fails) or **Geode crash log** (if the game crashes).

## Still unresolved — needs access to the real GD 2.2074 binary

- `src/mod/repair.hpp` has multiple player-state raw offsets calibrated on
  2.2081, including some used by solver reanchoring. They **must be measured
  against 2.2074 before a working solver can be guaranteed**.
- Other tracing and restore paths retain 2.2081 assumptions (see e.g.
  `src/mod/hooks_player.cpp`, `src/mod/hooks_gamelayer.cpp`, `src/mod/trace_io.hpp`).
- Geode hook binding/ABI compatibility and official-level solves have not been
  confirmed on the 2.2074 executable. Success of a Windows build will only
  show that the source compiled and packaged, not that it runs correctly.

Do not label a Geode artifact from this source a fully tested 2.2074 solver
until it survives in-game Normal → Replay → Solve smoke tests.
