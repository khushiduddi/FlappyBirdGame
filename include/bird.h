//
// Created by Khushi Duddi on 3/16/21
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
        Bird(const glm::vec2 setPosition, const vec2 setVelocity, int top, int bottom, bool isTest = false);

        /**
         * Returns a bird_'s position
         */
        glm::vec2 GetPosition() const;

        /**
         * Changes a bird's position to a given vec2
         * @param setPosition
         */
        void SetPosition(const vec2 setPosition);

        /**
         * Updates the velocities position each second based off the velocity and acceleration
         */
        void Move();

        /**
         * Sets the acceleration to a value greater than 0.
         */
        void Jump();

        /**
         * Changes the frame of the bird gif so the bird's wings flap and eyes blink.
         */
        void Flap();

        /**
         * Returns the bird image
         * @return
         */
        ci::gl::Texture2dRef GetTexture() const;

        /**
         * Returns an int which is the y position of top of the bird based
         * of the birds position on the screen
         * @return int
         */
        int GetTop() const;

        /**
         * Returns an int which is the y position of bottom of the bird based
         * of the birds position on the screen
         * @return int
         */
        int GetBottom() const;

        /**
         * Returns an int which is the x position of right of the bird based
         * of the birds position on the screen
         * @return int
         */
        int GetRight() const;

        /**
         * Returns an int which is the x position of left of the bird based
         * of the birds position on the screen
         * @return int
         */
        int GetLeft() const;

    private:
        glm::vec2 position_;
        glm::vec2 velocity_;
        int display_top_;
        int display_bottom_;
        ci::gl::Texture2dRef texture_;
        std::vector<ci::gl::Texture2dRef> textures_;
        int frame_index_;
        int frame_rate_;
        const int kFrameRate = 5;
        int acceleration_;

        int width_;
        int height_;
    };

}  // namespace flappybird

#endif  // FLAPPY_BIRD_BIRD_H
