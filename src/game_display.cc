#include "game_display.h"
#include "bird.h"
#include <utility>

namespace flappybird {

    using glm::vec2;

    GameDisplay::GameDisplay(const vec2 &top_left, size_t pixels_per_side)
            : top_left_(top_left), num_pixels_per_side_(pixels_per_side),
              engine_(), obstacle_offset_(pixels_per_side / 2), obstacle_start_index_(0),
              kBottomPosition(top_left_.y + num_pixels_per_side_ / 2) {
        std::cout << "top_left_: " << top_left_ << " num_pixels: " << num_pixels_per_side_ << std::endl;
        std::cout << "kBottom position: " << kBottomPosition << std::endl;
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

        for (size_t i = 0; i < kNumOfObstacles; i++) {
            // Create obstacles with random heights between positions 150 and 250
            obstacles_.push_back(rand() % (250 - 150) + 150);
        }
    }

    void GameDisplay::Display() const {
        if (engine_.GetGameStatus() == engine_.kGameNotStarted) {
            DisplayBackground();
            vec2 pos((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 2) / 2);
            ci::gl::drawStringCentered("Press enter to start game.", pos, ci::Color::white(),
                                       ci::Font(kFontName, kFontSize));

        }
        if (engine_.GetGameStatus() == engine_.kGameInProgress) {
            //ci::gl::color(kColor);
            DisplayBackground();

            if (!birds_.empty()) {
                for (Bird bird: birds_) {
                    ci::gl::color(ci::Color(5, 20, 0));
                    ci::gl::drawSolidCircle(bird.GetPosition(), bird.GetRadius());
                    ci::gl::color(ci::Color::white());
                }
            }

        }

        if (engine_.GetGameStatus() == engine_.kGameOver) {
            DisplayBackground();
            if (!birds_.empty()) {
                for (Bird bird: birds_) {
                    ci::gl::color(ci::Color(5, 20, 0));
                    ci::gl::drawSolidCircle(bird.GetPosition(), bird.GetRadius());
                    ci::gl::color(ci::Color::white());
                }
            }
            vec2 p1((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 2) / 2);
            ci::gl::drawStringCentered("Game over.", p1, ci::Color::white(), ci::Font(kFontName, kFontSize));
            vec2 p2((top_left_.x + num_pixels_per_side_) / 2, (top_left_.y + num_pixels_per_side_ / 3));
            std::string score = "Score: " + std::to_string(engine_.GetScore());
            ci::gl::drawStringCentered(score, p2, ci::Color::white(), ci::Font(kFontName, kFontSize));

        }

    }

    void GameDisplay::AdvanceOneFrame() {
        if (engine_.GetGameStatus() == GameEngine::kGameInProgress) {
            for (Bird &bird: birds_) {
                if (bird.GetPosition().y < kBottomPosition) {
                    if (obstacle_offset_ == 30) {
                        int bird_at = (obstacle_start_index_ + 1) % kNumOfObstacles;
                        std::cout << "Bird at:  " << bird_at << " Position: " << bird.GetPosition().y << " Height: "
                                  << obstacles_[bird_at] << std::endl;
                        if (bird.GetPosition().y <= obstacles_[bird_at]) {
                            std::cout << "Bird hit top of obstacle. \n";
                            engine_.SetGameStatus(engine_.kGameOver);
                        }
                        if (bird.GetPosition().y > obstacles_[bird_at] + kObstacleGap) {
                            std::cout << "Bird hit bottom of obstacle. \n";
                            engine_.SetGameStatus(engine_.kGameOver);
                        }
                        engine_.AddScore();
                    }
                    bird.Move();
                }
                if (bird.GetPosition().y >= kBottomPosition) {
                    engine_.SetGameStatus(engine_.kGameOver);
                }
            }
            obstacle_offset_ -= 1;
            if (obstacle_offset_ == -(kObstacleThickness + top_left_.x)) {
                obstacle_offset_ += kSpaceBetweenObstacles;
                obstacle_start_index_ = (obstacle_start_index_ + 1) % kNumOfObstacles;
            }
        }
    }

    void GameDisplay::Clear() {
        birds_.clear();
        engine_.SetGameStatus(GameEngine::kGameOver);
    }

    void GameDisplay::Jump() {
        if (engine_.GetGameStatus() == GameEngine::kGameInProgress) {
            for (Bird &bird: birds_) {
                if (bird.GetPosition().y < kBottomPosition && bird.GetPosition().y > top_left_.y + 2 * kBirdRadius) {
                    bird.Jump();
                }
            }
        }
    }

    void GameDisplay::DisplayBackground() const {
        ci::gl::clear();
        ci::gl::draw(texture_);
        ci::gl::drawStrokedRect(
                ci::Rectf(top_left_, top_left_ + ci::vec2((num_pixels_per_side_), (num_pixels_per_side_ / 2))));
        ci::gl::drawString("Score: " + std::to_string(engine_.GetScore()), top_left_, ci::Color::white(),
                           ci::Font(kFontName, kFontSize));
        if (engine_.GetGameStatus() != engine_.kGameNotStarted) {
            int x = top_left_.x + obstacle_offset_;
            for (size_t i = 0; i < kNumOfObstacles; i++) {
                int j = (obstacle_start_index_ + i) % kNumOfObstacles;
                vec2 pos(x, 10);
                //if (pos.x > 200 && pos.x < 200 + kObstacleThickness)
                //std::cout << "start index: " << obstacle_start_index_ << " offset: " << obstacle_offset_ << " j: " << j << " pos: " << pos << std::endl;
                DrawObstacle(obstacles_[j], pos);
                x += kSpaceBetweenObstacles;
            }
        }
    }

    int GameDisplay::SetEngineStatus(int status) {
        return engine_.SetGameStatus(status);
    }

    void GameDisplay::DrawObstacle(int height, vec2 pos1) const {
        vec2 pos2(pos1.x + kObstacleThickness, pos1.y + height);
        ci::gl::color(ci::Color(0, 20, 10));
        ci::gl::drawSolidRect(ci::Rectf(pos1, pos2));

        vec2 pos3(pos1.x, pos2.y + kObstacleGap);
        vec2 pos4(pos1.x + kObstacleThickness, kBottomPosition);
        ci::gl::drawSolidRect(ci::Rectf(pos3, pos4));
        ci::gl::color(ci::Color::white());
    }

}  // namespace flappybird
