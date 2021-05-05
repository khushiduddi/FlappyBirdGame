#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_display.h"

namespace flappybird {

/**
 * An app for the game flappybird.
 */
    class Game : public ci::app::App {
    public:
        Game();

        void draw() override;

        void update() override;

        void keyDown(ci::app::KeyEvent event) override;

        const double kMargin = 10;
        // Area inside boundary
        const size_t kImageDimension = 960;
        // Area of whole window
        const double kSizeOfWindow = kImageDimension + 4 * kMargin;

    private:
        GameDisplay gameDisplay_;
    };

}  // namespace flappybird
