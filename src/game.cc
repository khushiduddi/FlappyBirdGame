#include "game.h"

namespace flappybird {

    Game::Game() : screen_(glm::vec2(2 * kMargin, kMargin), kImageDimension) {
        ci::app::setWindowSize((int) kSizeOfWindow, (int) kSizeOfWindow / 2);
    }

    void Game::draw() {
        //ci::Color background_color(150, 220, 160);
        //ci::gl::clear(background_color);
        //ci::gl::clear();
        ci::gl::draw(texture_);
        screen_.Display();
    }

    void Game::update() {
        screen_.AdvanceOneFrame();
    }

    void Game::keyDown(ci::app::KeyEvent event) {
        if (event.getCode() == ci::app::KeyEvent::KEY_RETURN)
            screen_.Clear();
        if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
            screen_.Jump();
        }
    }


}  // namespace flappybird
