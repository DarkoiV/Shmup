#include "game.hpp"

int main() 
{
    Game::loadSettings();
    
    Game game;
    game.run();
}
