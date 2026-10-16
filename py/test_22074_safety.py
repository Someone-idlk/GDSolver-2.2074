"""Lightweight static regression gates for the conservative GD 2.2074 port.

Not a substitute for compilation or in-game testing against GD 2.2074.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
read = lambda path: (root / path).read_text()

compat = read("src/mod/port_compat.hpp")
config = read("src/mod/config.hpp")
playlayer = read("src/mod/hooks_playlayer.cpp")
gamelayer = read("src/mod/hooks_gamelayer.cpp")
playmenu = read("src/mod/hooks_playmenu.cpp")

assert "verifiedProcessRng = false" in compat
assert "inline bool g_rngFix = false" in config
assert "if (!compat::verifiedProcessRng) return" in config
assert "if (g_rngFresh && compat::verifiedProcessRng)" in playlayer
assert "&& compat::verifiedProcessRng" in playlayer
assert "pl->removeCheckpoint(false)" in gamelayer
assert "reinterpre" not in gamelayer[gamelayer.index("static void clearCheckpointsUnsectioned"):gamelayer.index("// The process's working set")]
for off in ("0x1e0", "0x275", "0x1a0", "0x434"):
    assert f"static_assert(offsetof(" not in playmenu
assert "fixed while the bot drives" not in playmenu
print("GD 2.2074 conservative port safety gates: PASS")
