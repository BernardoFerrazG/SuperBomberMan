# Super BomberMan

A local two-player arena game written in **C** with **[raylib](https://www.raylib.com/)**. Players plant bombs, blow up destructible barriers, collect power-ups and try to catch each other in an explosion before the two-minute timer runs out. The in-game text is in Portuguese; this README is in English.

## Gameplay

| | Player 1 | Player 2 |
| --- | --- | --- |
| Move | `W` `A` `S` `D` | Arrow keys |
| Plant bomb | `Space` | Numpad `Enter` |

- Each match lasts **2 minutes**. Catching your opponent in an explosion wins the round, and the scoreboard carries over between rounds.
- Bombs explode after **3 seconds**, in a cross pattern. An explosion that reaches another bomb **detonates it early** (chain reaction).
- Destroying a barrier can reveal a power-up: **speed**, **extra bomb** (up to 10) or **longer explosions**.
- Players type their names on the start screen, and final scores are appended to `placar.txt`.
- There are two arenas, each with its own characters.

## Build and run

Requires a C11 compiler and raylib 5.x.

```bash
# Ubuntu/Debian: build raylib from source (https://github.com/raysan5/raylib#build-and-installation)
# macOS: brew install raylib
cd src
make          # build ./jogo
make run      # must be run from src/ (assets are loaded from images/ and musics/)
```

## Code structure

```
src/
├── main.c             # Window, audio and asset loading; main loop
├── jogo.h             # Game state (Game, Map, Hero, Bomb, Powerup) and module interfaces
├── hero.c             # Movement, rendering and hit detection for players
├── bomb.c             # Bomb lifecycle, explosion growth, chain reactions, power-ups
├── map.c              # Arena layouts, barriers and power-up placement
├── barrier_border.c   # Collision with walls and arena borders
├── telas.c            # Screens: start menu, name input, round result, timer, scoreboard
├── images/  musics/   # Sprites and soundtrack
└── Makefile
```

Each frame, the game updates the whole state (`UpdateGame`) and then renders it (`DrawGame`). Collisions use raylib's axis-aligned rectangle checks: an explosion is four rectangles that grow each frame until they hit a wall or reach the bomb's range.

## Bug fixes in this revision

- **Undefined behaviour in hit detection.** `deathHero` had no return value when the explosion missed, so a garbage value could register a hit on a player who wasn't caught.
- **Buffer overflow.** Collecting more than 9 extra-bomb power-ups wrote past the end of the 10-slot bomb array. The count is now capped.
- **Chain reactions between players** checked the wrong player's bomb. An explosion from player 1 now correctly detonates player 2's bombs, and vice versa.
- **Asymmetric gameplay.** Player 1's explosions only destroyed barriers vertically, while player 2's worked in all four directions. Both now use the same rule.
- **Range power-up** only affected the first bomb slot. It now applies to all of a player's bombs.
- **Bomb timer precision.** Plant times were stored as `int`, which truncated `GetTime()`, so fuses varied by up to a second. They are now stored as `double`.
- **Closing the window** from a menu called `CloseWindow()` and then kept drawing to it. The game now saves the scoreboard and exits cleanly.
- Smaller fixes: the game no longer loads a sprite that doesn't exist, it releases the audio device on exit, it uses `snprintf` instead of `sprintf`/`strcpy`, and it builds warning-free with `-Wall -Wextra -Werror`. The compiled binary was removed from the repository.
