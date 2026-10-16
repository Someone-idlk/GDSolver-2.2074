# GDSolver 2.2074

Geometry Dash 2.2074 automatic level solver (Geode mod).

## Add the repaired source (one ZIP upload)

1. Download `GDSolver_2.2074_repaired_source.zip` from our ChatGPT conversation.
2. On this repository's **Code** tab, click **Add file → Upload files**.
3. Upload **the ZIP itself**, without unzipping it, to the repository root. Keep its filename exactly `GDSolver_2.2074_repaired_source.zip`.
4. Click **Commit changes** to the `main` branch.
5. Open **Actions → Import repaired GDSolver source**. The import will unpack the complete project, remove the ZIP from the latest revision, and commit the source code.
6. After the import finishes, open **Actions → Build → Run workflow** to attempt a Windows `.geode` build.

**Important:** This is a conservative repair port of the original solver. The Geode mod has not yet been compiled or run inside GD 2.2074; binary offset compatibility remains to be validated. Keep a game-data backup before first testing.
