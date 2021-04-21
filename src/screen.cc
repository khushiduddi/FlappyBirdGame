#include "screen.h"
#include "bird.h"
#include <utility>

namespace flappybird {

    using glm::vec2;

    Screen::Screen(const vec2 &top_left, size_t pixels_per_side)
            : top_left_(top_left), num_pixels_per_side_(pixels_per_side),
              kBottomPosition(top_left_.y + num_pixels_per_side_ / 2 - 20) {
        //ci::gl::Texture2dRef texture_;
        auto background = ci::loadImage(
                "/Users/khushiduddi/Downloads/Cinder/my-projects/final-project-kduddi2/data/flappbirdbackground.png");
        texture_ = ci::gl::Texture2d::create(background);
        vec2 pos_1(200, 200);

        Bird flappy_bird = Bird(pos_1, kBirdVelocity, kBirdRadius, kBirdMass, kBirdColor);

        for (size_t count = 0; count < kNumOfBirds; count++) {
            Bird bird = flappy_bird;
            birds_.push_back(bird);
        }

    }

    void Screen::Display() const {
        ci::gl::clear();
        ci::gl::draw(texture_);
        //ci::gl::color(kColor);
        ci::gl::drawStrokedRect(ci::Rectf(top_left_, top_left_ + ci::vec2((num_pixels_per_side_),
                                                                          (num_pixels_per_side_ / 2))));

        if (!birds_.empty()) {
            for (Bird bird: birds_) {
                //ci::gl::color(bird.GetColor());
                std::cout << "drawing at position: " << bird.GetPosition() << "\n";
                ci::gl::drawSolidCircle(bird.GetPosition(), bird.GetRadius());
                //ci::gl::clearColor(kColor);
            }
        }

    }

    void Screen::AdvanceOneFrame() {
        for (Bird &bird: birds_) {
            if (bird.GetPosition().y < kBottomPosition) {
                bird.Move();
            }
        }
    }

    void Screen::Clear() {
        birds_.clear();
    }

    void Screen::Jump() {
        for (Bird &bird: birds_) {
            if (bird.GetPosition().y < kBottomPosition && bird.GetPosition().y > top_left_.y + 2 * kBirdRadius) {
                bird.Jump();
            }
        }
    }

}  // namespace flappybird
