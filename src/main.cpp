/*
Rolling Thunder (https://github.com/Ninjune/Rolling-Thunder)
desc: Rolling thunder is a side scrolling arcade game where the main character, Albatross,
tries to take out enemies to earn points. Eventually, after making it past 10 levels,
Albatross must take out the final boss Maboo to complete the game.


Authors:
Andrew T
Phillip C
Trey C

Keymap:
(Debug)
F5

(Menu)
5 - Add credit
6 - Player one button

(Ingame)
W - Enter door/hold when jumping to get on rails
D - Move right
A - Move left
F - Jump
R - Shoot

What needs work:
- more animations
- enemy recolors/other enemies
- other levels
- UI needs finished/polishing

We did not cheat.
*/
#include <SFML/Graphics.hpp>
#include "Game/Game.h"
#include"Entity/Player/Player.h"


int main()
{
    // this MUST be called first. loads the textures.
    AnimationData::load();

    Game game;
    game.run();
    return 0;
}