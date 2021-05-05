#include "game_display.h"
#include "bird.h"
#include <utility>
#include "cinder/app/app.h"

namespace flappybird {

    using glm::vec2;

    GameDisplay::GameDisplay(const vec2 &top_left, size_t pixels_per_side)
            : top_left_(top_left), num_pixels_per_side_(pixels_per_side),
              kBottomPosition(top_left_.y + num_pixels_per_side_ / 2),
              bird_(vec2(kBirdStartPos, kBirdStartPos), vec2(kBirdVelocity, kBirdVelocity), top_left.y,
                    kBottomPosition),
              obstacle_offset_(pixels_per_side / 2), obstacle_start_index_(0) {

        game_status_ = kGameNotStarted;
        score_ = 0;

        texture_ = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadResource("flappybirdbackground.png")));
        texture_pipe_bottom_ = ci::gl::Texture2d::create(
                ci::loadImage(ci::app::loadResource("flappy-bird-pipe-bottom.png")));
        texture_pipe_top_ = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadResource("flappy-bird-pipe-top.png")));

        for (size_t i = 0; i < kNumOfObstacles; i++) {
            // Create obstacles with random heights between positions 150 and 250
            obstacles_.push_back(rand() % (250 - 150) + 150);
        }
    }

    void GameDisplay::Display() const {
        if (game_status_ == kGameNotStarted) {
            DisplayBackground();
            DrawBird();
            vec2 pos((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 2) / 2);
            ci::gl::drawStringCentered("Press enter to start game.", pos, ci::Color::white(),
                                       ci::Font(kFontName, kFontSize));
        }
        if (game_status_ == kGameInProgress) {
            DisplayBackground();
            DrawBird();
        }
        if (game_status_ == kGamePaused) {
            DisplayBackground();
            DrawBird();
            vec2 pos((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 2) / 2);
            ci::gl::drawStringCentered("Press enter to resume game.", pos, ci::Color::white(),
                                       ci::Font(kFontName, kFontSize));
        }
        if (game_status_ == kGameOver) {
            DisplayBackground();
            DrawBird();
            vec2 p1((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 2) / 2);
            ci::gl::drawStringCentered("Game over.", p1, ci::Color::white(), ci::Font(kFontName, kFontSize));
            vec2 p2((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 3));
            std::string score = "Score: " + std::to_string(score_);
            ci::gl::drawStringCentered(score, p2, ci::Color::white(), ci::Font(kFontName, kFontSize));
        }
    }

    void GameDisplay::AdvanceOneFrame() {
        bird_.Flap();
        if (game_status_ == kGameInProgress) {
            if (bird_.GetBottom() < kBottomPosition) {
                int bird_at = -1;
                // Check if bird is at an obstacle
                if (bird_.GetRight() >= top_left_.x + obstacle_offset_ &&
                    bird_.GetLeft() <= top_left_.x + obstacle_offset_ + kObstacleThickness) {
                    bird_at = obstacle_start_index_;
                }
                if (bird_.GetRight() >= top_left_.x + obstacle_offset_ + kSpaceBetweenObstacles &&
                    bird_.GetLeft() <= top_left_.x + obstacle_offset_ + kObstacleThickness + kSpaceBetweenObstacles) {
                    bird_at = (obstacle_start_index_ + 1) % kNumOfObstacles;
                }
                if (bird_at >= 0) {
                    // Bird hit top of obstacle
                    if (bird_.GetTop() <= (obstacles_[bird_at] + top_left_.y)) {
                        SetGameStatus(kGameOver);
                    }
                        // Bird hit bottom of obstacle
                    else if (bird_.GetBottom() > obstacles_[bird_at] + top_left_.y + kObstacleGap) {
                        SetGameStatus(kGameOver);
                    }
                        // Checking if bird has successfully passed an obstacle
                    else if (bird_.GetLeft() == top_left_.x + obstacle_offset_ + kObstacleThickness ||
                             bird_.GetLeft() ==
                             top_left_.x + obstacle_offset_ + kObstacleThickness + kSpaceBetweenObstacles) {
                        score_++;
                    }
                }
                bird_.Move();
            }
            if (bird_.GetBottom() >= kBottomPosition) {
                SetGameStatus(kGameOver);
            }

            obstacle_offset_ -= 1;
            if (obstacle_offset_ == -(kObstacleThickness + top_left_.x)) {
                obstacles_[obstacle_start_index_] = rand() % (250 - 150) + 150;
                obstacle_offset_ += kSpaceBetweenObstacles;
                obstacle_start_index_ = (obstacle_start_index_ + 1) % kNumOfObstacles;
            }
        }
    }

    void GameDisplay::EndGame() {
        SetGameStatus(kGameOver);
    }

    void GameDisplay::Jump() {
        if (game_status_ == kGameInProgress) {
            if (bird_.GetBottom() < kBottomPosition &&
                bird_.GetTop() > top_left_.y) {
                bird_.Jump();
            }
        }
    }

    void GameDisplay::DisplayBackground() const {
        ci::gl::clear();
        ci::gl::draw(texture_);
        ci::gl::drawStrokedRect(
                ci::Rectf(top_left_, top_left_ + ci::vec2((num_pixels_per_side_), (num_pixels_per_side_ / 2))));
        if (game_status_ != kGameNotStarted) {
            int x = top_left_.x + obstacle_offset_;
            for (size_t i = 0; i < kNumOfObstacles; i++) {
                int j = (obstacle_start_index_ + i) % kNumOfObstacles;
                vec2 pos(x, 10);
                DrawObstacle(obstacles_[j], pos);
                x += kSpaceBetweenObstacles;
            }
        }
        vec2 pos(top_left_.x + 10, top_left_.y + 10);
        ci::gl::drawString("Score: " + std::to_string(score_), pos, ci::Color::white(),
                           ci::Font(kFontName, kFontSize));
    }

    int GameDisplay::SetGameStatus(int status) {
        if (status < kGameNotStarted || status > kGameOver) {
            return -1;
        }
        // Game progresses through these states
        // NotStarted -> InProgress ------+-----> Over
        //                  ^ ^           |        |
        //                  | +-- Pause --+        |
        //                  |                      |
        //                  +----------------------+
        if ((game_status_ == kGameNotStarted && status != kGameInProgress) ||
            (game_status_ == kGameInProgress && !(status == kGameOver || status == kGamePaused)) ||
            (game_status_ == kGamePaused && status != kGameInProgress) ||
            (game_status_ == kGameOver && status != kGameInProgress)) {
            return -1;
        }
        game_status_ = status;
        return 0;
    }

    void GameDisplay::DrawObstacle(int height, vec2 pos1) const {
        vec2 pos2(pos1.x + kObstacleThickness, pos1.y + height);
        ci::gl::draw(texture_pipe_top_, ci::Rectf(pos1, pos2));

        vec2 pos3(pos1.x, pos2.y + kObstacleGap);
        vec2 pos4(pos1.x + kObstacleThickness, kBottomPosition);
        ci::gl::draw(texture_pipe_bottom_, ci::Rectf(pos3, pos4));
    }

    void GameDisplay::DrawBird() const {
        ci::gl::draw(bird_.GetTexture(), vec2(bird_.GetLeft(), bird_.GetTop()));
    }

    void GameDisplay::StartGame() {
        int previous_status = game_status_;
        if (SetGameStatus(kGameInProgress) < 0) {
            return;
        }
        if (previous_status == kGamePaused) {
            return;
        }
        bird_.SetPosition(vec2(kBirdStartPos, kBirdStartPos));
        obstacle_offset_ = num_pixels_per_side_ / 2;
        obstacle_start_index_ = 0;
        score_ = 0;
    }

    void GameDisplay::PauseGame() {
        if (SetGameStatus(kGamePaused) < 0) {
            return;
        }
    }
}  // namespace flappybird
