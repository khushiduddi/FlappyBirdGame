#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "screen.h"

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
        const size_t kImageDimension = 960;
        const double kSizeOfWindow = kImageDimension + 4 * kMargin;

    private:
        Screen screen_;
        ci::gl::Texture2dRef texture_;
    };

}  // namespace flappybird
