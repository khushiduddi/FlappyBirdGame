#include "game.h"

namespace flappybird {

    Game::Game() : gameDisplay_(glm::vec2(2 * kMargin, kMargin), kImageDimension) {
        ci::app::setWindowSize((int) kSizeOfWindow, (int) kSizeOfWindow / 2);
    }

    void Game::draw() {
        //ci::Color background_color(150, 220, 160);
        //ci::gl::clear(background_color);
        //ci::gl::clear();
        gameDisplay_.Display();
    }

    void Game::update() {
        gameDisplay_.AdvanceOneFrame();
    }

    void Game::keyDown(ci::app::KeyEvent event) {
        if (event.getCode() == ci::app::KeyEvent::KEY_DELETE)
            gameDisplay_.Clear();
        if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
            gameDisplay_.Jump();
        }
        if (event.getCode() == ci::app::KeyEvent::KEY_RETURN)
            gameDisplay_.SetEngineStatus(GameEngine::kGameInProgress);
    }


}  // namespace flappybird
