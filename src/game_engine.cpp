//
// Created by Khushi Duddi on 4/25/21.
//
#include "game_engine.h"

namespace flappybird {
    GameEngine::GameEngine() {
        game_status_ = kGameNotStarted;
        score_ = 0;
    }

    int GameEngine::GetGameStatus() const {
        return game_status_;
    }

    int GameEngine::SetGameStatus(int status) {
        if (status < kGameNotStarted || status > kGameOver) {
            return -1;
        }
        // Implement the game state machine
        game_status_ = status;
        return 0;
    }

    int GameEngine::GetScore() const {
        return score_;
    }

    int GameEngine::SetScore(int score) {
        score_ = score;
        return score;
    }

    void GameEngine::AddScore() {
        score_++;
    }
}

