#pragma once

#include "cinder/gl/gl.h"
#include "bird.h"

using glm::vec2;

namespace flappybird {

/**
 * The container in which the bird and other game elements are contained.
 * This class stores the bird and updates it on each frame of the game.
 */
    class Screen {
    public:

        Screen(const glm::vec2 &top_left, size_t pixels_per_side);

        /**
         * Displays the background and bird.
         */
        void Display() const;

        /**
         * Updates the positions and velocities of the bird.
         */
        void AdvanceOneFrame();

        void Jump();

        /**
         * Removes the bird.
         * */
        void Clear();


    private:

        glm::vec2 top_left_;

        size_t num_pixels_per_side_;

        std::vector<Bird> birds_;

        //cinder::Path2d texture_;
        ci::gl::Texture2dRef texture_;

        const glm::vec2 kBirdVelocity = glm::vec2(2, 2);

        const double kBirdRadius = 20;

        const float kBirdMass = 50;

        const ci::Color kBirdColor = ci::Color::hex(0x9B0000);

        const ci::Color kColor = ci::Color::black();

        const size_t kNumOfBirds = 1;

        const int kBottomPosition;

    };

}  // namespace flappybird
