/*
Rolling Thunder (https://github.com/Ninjune/Rolling-Thunder)
An arcade game

Authors:

Keymap:
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