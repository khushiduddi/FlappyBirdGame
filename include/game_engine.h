//
// Created by Khushi Duddi on 4/25/21.
//

#ifndef FINAL_PROJECT_KDUDDI2_GAME_ENGINE_H
#define FINAL_PROJECT_KDUDDI2_GAME_ENGINE_H

#pragma once

#include "cinder/gl/gl.h"
#include "bird.h"

using glm::vec2;

namespace flappybird {

/**
 * The core of the flappy bird game.
 */
    class GameEngine {
    public:
        GameEngine();

        int GetGameStatus() const;

        int SetGameStatus(int status);

        int GetScore() const;

        int SetScore(int score);

        void AddScore();

        static const int kGameNotStarted = 0;
        static const int kGameInProgress = 1;
        static const int kGameOver = 2;

    private:
        int game_status_;
        int score_;
    };

}

#endif //FINAL_PROJECT_KDUDDI2_GAME_ENGINE_H
