#pragma once

#include "cinder/gl/gl.h"
#include "bird.h"
#include "game_engine.h"

using glm::vec2;

namespace flappybird {

/**
 * The container in which the bird and other game elements are contained.
 * This class stores the bird and updates it on each frame of the game.
 */
    class GameDisplay {
    public:

        GameDisplay(const glm::vec2 &top_left, size_t pixels_per_side);

        /**
         * Displays the background and the bird.
         */
        void Display() const;

        /**
         * Updates the positions and velocities of the bird.
         */
        void AdvanceOneFrame();

        void Jump();

        int SetEngineStatus(int status);

        /**
         * Removes the bird.
         * */
        void Clear();


    private:

        void DisplayBackground() const;

        void DrawObstacle(int height, vec2 pos1) const;

        glm::vec2 top_left_;
        size_t num_pixels_per_side_;
        GameEngine engine_;

        std::vector<Bird> birds_;
        std::vector<int> obstacles_;
        int obstacle_offset_;
        int obstacle_start_index_;

        ci::gl::Texture2dRef texture_;

        const glm::vec2 kBirdVelocity = glm::vec2(2, 2);
        const double kBirdRadius = 20;
        const float kBirdMass = 50;
        const ci::Color kBirdColor = ci::Color::hex(0x9B0000);

        const size_t kNumOfBirds = 1;
        const size_t kNumOfObstacles = 7;
        const size_t kObstacleGap = 120;
        const size_t kSpaceBetweenObstacles = 150;
        const size_t kObstacleThickness = 50;

        const int kBottomPosition;

        const float kFontSize = 32;
        const std::string kFontName = "Arial";


    };

}  // namespace flappybird
