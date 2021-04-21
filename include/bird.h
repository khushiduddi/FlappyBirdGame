//
// Created by Khushi Duddi on 3/16/21.
//

#ifndef FLAPPY_BIRD_BIRD_H
#define FLAPPY_BIRD_BIRD_H


#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace flappybird {

    class Bird {
    public:

        /**
         * Creates a Bird with a position an velocity
         */
        Bird(const glm::vec2 &setPosition, const vec2 &setVelocity, double rad, double mass, ci::Color color);

        /**
         * Returns a bird's velocity
         */
        //&
        glm::vec2 GetVelocity();

        /**
         * Returns a bird's position
         */
        glm::vec2 GetPosition();

        /**
         * Returns a bird's position
         */
        float GetRadius() const;

        /**
         * Returns a color position
         */
        ci::Color GetColor();

        /**
         * Returns a mass position
         */
        float GetMass();

        /**
         * Changes the velocity of a bird with a given velocity vector
         */
        void SetVelocity(const glm::vec2 &new_vel) { velocity_ = new_vel; }


        /**
         * Updates the velocities position each second based off the velocity
         */
        void Move();

        void Jump();

    private:
        glm::vec2 position_;
        glm::vec2 velocity_;
        double radius_;
        double mass_;
        ci::Color color_;
    };

}  // namespace flappybird

#endif  // FLAPPY_BIRD_BIRD_H
