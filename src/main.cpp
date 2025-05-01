/*
Rolling Thunder
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