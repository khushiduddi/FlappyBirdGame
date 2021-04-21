#include "game.h"

using flappybird::Game;

void prepareSettings(Game::Settings *settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function
CINDER_APP(Game, ci::app::RendererGl, prepareSettings);
