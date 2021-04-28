//
// Created by Khushi Duddi on 3/16/21
//
#include "bird.h"
#include "cinder/gl/gl.h"

namespace flappybird {

    Bird::Bird(const vec2 &setPosition, const vec2 &setVelocity, const double rad, double mass, ci::Color color) {
        position_ = setPosition;
        velocity_ = setVelocity;
        radius_ = rad;
        mass_ = mass;
        color_ = color;
    }

    glm::vec2 flappybird::Bird::GetPosition() const {
        const vec2 &pos = position_;
        return pos;
    }

    glm::vec2 flappybird::Bird::GetVelocity() const {
        const vec2 &vel = velocity_;
        return vel;
    }

    float flappybird::Bird::GetRadius() const {
        const float rad = radius_;
        return rad;
    }

    float flappybird::Bird::GetMass() const {
        const float mass = mass_;
        return mass;
    }

    ci::Color flappybird::Bird::GetColor() const {
        const ci::Color &col = color_;
        return col;
    }

    void flappybird::Bird::Move() {
        position_.y += velocity_.y;
    }

    void Bird::Jump() {
        position_.y -= velocity_.y * 15;
    }


}  //namespace flappybird