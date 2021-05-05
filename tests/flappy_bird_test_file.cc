#include <catch2/catch.hpp>

#include "game_display.h"
#include "game.h"
#include "bird.h"

using flappybird::GameDisplay;
using flappybird::Bird;

TEST_CASE("Test bird getters and setters to make sure they work correctly.") {
    vec2 pos(4, 30);
    vec2 vel(2, 1);
    Bird test_bird(pos, vel, 0, 50, true);
    SECTION("Test bird method GetPosition") {
        REQUIRE(test_bird.GetPosition().x == Approx(4));
        REQUIRE(test_bird.GetPosition().y == Approx(30));
    }

    SECTION("Test bird method SetPosition.") {
        test_bird.SetPosition(vec2(6, 6));
        REQUIRE(test_bird.GetPosition().x == Approx(6));
        REQUIRE(test_bird.GetPosition().y == Approx(6));
    }
}

TEST_CASE("Testing bird methods GetTop, GetBottom, GetLeft, GetRight.") {
    vec2 pos(19, 35);
    vec2 vel(2, 1);
    Bird test_bird(pos, vel, 0, 50, true);
    SECTION("Testing GetTop based of the height") {
        REQUIRE(test_bird.GetTop() == 30);
    }SECTION("Testing GetBottom based of the height") {
        REQUIRE(test_bird.GetBottom() == 40);
    }SECTION("Testing GetLeft based of the width") {
        REQUIRE(test_bird.GetLeft() == 14);
    }SECTION("Testing GetRight based of the width") {
        REQUIRE(test_bird.GetRight() == 24);
    }
}

TEST_CASE("Check bird_ position after executing move method.") {
    SECTION("Move method when bird is within screen.") {
        vec2 pos(2, 5);
        vec2 vel(2, 1);
        Bird test_bird(pos, vel, 0, 50, true);
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(5));
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(6));
    }

    SECTION("Move method when bird is about to hit the bottom of the screen.") {
        vec2 pos(2, 42);
        vec2 vel(2, 1);
        Bird test_bird(pos, vel, 0, 50, true);
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(43));
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(44));
        test_bird.Move();
        // Bottom of bird hit bottom of screen
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(45));
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(2));
        REQUIRE(test_bird.GetPosition().y == Approx(45));
    }
}

TEST_CASE("Check bird_ position after jump method called.") {
    SECTION("Jump method called.") {
        vec2 pos(5, 50);
        vec2 vel(5, 1);
        Bird test_bird(pos, vel, 0, 100, true);
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(50));
        test_bird.Jump();
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(45));
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(41));
    }

    SECTION("Jump method called when bird is about to hit the top of the screen.") {
        vec2 pos(5, 15);
        vec2 vel(5, 1);
        Bird test_bird(pos, vel, 0, 100, true);
        test_bird.Jump();
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(10));
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(6));
        test_bird.Jump();
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(5));
        test_bird.Jump();
        test_bird.Move();
        REQUIRE(test_bird.GetPosition().x == Approx(5));
        REQUIRE(test_bird.GetPosition().y == Approx(5));
    }
}