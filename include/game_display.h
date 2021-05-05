#pragma once

#include "cinder/gl/gl.h"
#include "bird.h"

using glm::vec2;

namespace flappybird {

/**
 * The container in which the bird_ and other game elements are contained.
 * This class stores the bird_ and updates it on each frame of the game.
 */
    class GameDisplay {
    public:

        GameDisplay(const glm::vec2 &top_left, size_t pixels_per_side);

        /**
         * Displays the background and the bird_.
         */
        void Display() const;

        /**
         * Starts a game and resets the pregame conditions based off the previous status
         */
        void StartGame();

        /**
         * Updates the positions of the bird_ and the obstacles.
         */
        void AdvanceOneFrame();

        /**
         * Called the bird jump method if certain conditions are met.
         */
        void Jump();

        /**
         * Sets the game status to a given int which is one of the designated game statuses.
         * @param status
         * @return
         */
        int SetGameStatus(int status);

        /**
         * Pauses the game freezing the screen
         */
        void PauseGame();

        /**
         * Changes status to kGameOver and ends the game.
         * */
        void EndGame();


    private:

        void DisplayBackground() const;

        void DrawObstacle(int height, vec2 pos1) const;

        void DrawBird() const;

        glm::vec2 top_left_;
        size_t num_pixels_per_side_;
        const int kBottomPosition;
        //GameEngine engine_;

        Bird bird_;
        std::vector<int> obstacles_;
        int obstacle_offset_;
        int obstacle_start_index_;

        ci::gl::Texture2dRef texture_;
        ci::gl::Texture2dRef texture_pipe_top_;
        ci::gl::Texture2dRef texture_pipe_bottom_;

        static const int kBirdVelocity = 2;
        static const int kBirdStartPos = 200;

        static const size_t kNumOfObstacles = 7;
        static const size_t kObstacleGap = 120;
        static const size_t kSpaceBetweenObstacles = 150;
        static const size_t kObstacleThickness = 50;

        static const int kGameNotStarted = 0;
        static const int kGameInProgress = 1;
        static const int kGamePaused = 2;
        static const int kGameOver = 3;

        int game_status_;
        int score_;

        const float kFontSize = 32;
        const std::string kFontName = "Arial";


    };

}  // namespace flappybird
