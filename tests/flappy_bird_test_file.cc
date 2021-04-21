#include <catch2/catch.hpp>

#include <screen.h>
#include <bird.h>

using flappybird::Screen;
using flappybird::Bird;

TEST_CASE("Check bird position after executing move method.") {
    glm::vec2 pos(2, 5);
    glm::vec2 vel(2, 1);
    Bird test_bird(pos, vel, 10, 10, ci::Color::black());
    test_bird.Move();
    REQUIRE(test_bird.GetPosition().x == Approx(2));
    REQUIRE(test_bird.GetPosition().y == Approx(6));
    test_bird.Move();
    test_bird.Move();
    REQUIRE(test_bird.GetPosition().x == Approx(2));
    REQUIRE(test_bird.GetPosition().y == Approx(8));
}

TEST_CASE("Check bird position after jump method called.") {
    glm::vec2 pos(5, 30);
    glm::vec2 vel(5, 1);
    Bird test_bird(pos, vel, 10, 10, ci::Color::black());
    test_bird.Jump();
    REQUIRE(test_bird.GetPosition().x == Approx(5));
    REQUIRE(test_bird.GetPosition().y == Approx(15));
    test_bird.Move();
    REQUIRE(test_bird.GetPosition().x == Approx(5));
    REQUIRE(test_bird.GetPosition().y == Approx(16));
}