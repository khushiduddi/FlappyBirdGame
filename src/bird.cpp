//
// Created by Khushi Duddi on 3/16/21
//
#include "bird.h"
#include "cinder/gl/gl.h"
#include "cinder/app/app.h"

namespace flappybird {

    Bird::Bird(const vec2 setPosition, const vec2 setVelocity, int top, int bottom, bool isTest) {
        position_ = setPosition;
        velocity_ = setVelocity;
        display_top_ = top;
        display_bottom_ = bottom;
        frame_index_ = 0;
        frame_rate_ = 0;
        acceleration_ = 0;
        if (!isTest) {
            texture_ = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadResource("flappybird.gif")));
            ci::ImageSource::Options options;
            options.index(0);
            ci::ImageSourceRef img = ci::loadImage(ci::app::loadResource("flappybird.gif"));
            for (int i = 0; i < img->getCount(); ++i) {
                ci::gl::Texture2dRef frame = ci::gl::Texture2d::create(
                        loadImage(ci::app::loadResource("flappybird.gif"), options));
                textures_.push_back(frame);
                options.index(options.getIndex() + 1);
            }
            width_ = textures_[0]->getWidth();
            height_ = textures_[0]->getHeight();
        } else {
            width_ = 10;
            height_ = 10;
        }
    }

    glm::vec2 flappybird::Bird::GetPosition() const {
        const vec2 &pos = position_;
        return pos;
    }

    void flappybird::Bird::Move() {
        // Implementing jump acceleration
        if (acceleration_ > 0) {
            position_.y -= velocity_.y * acceleration_;
            acceleration_--;
        } else {
            position_.y += velocity_.y;
        }
        if (GetTop() < display_top_) {
            position_.y = display_top_ + height_ / 2;
        }
        if (GetBottom() > display_bottom_) {
            position_.y = display_bottom_ - height_ / 2;
        }
    }

    void Bird::Jump() {
        acceleration_ = 5;
        //position_.y -= velocity_.y * 15;
    }

    void Bird::Flap() {
        if (frame_rate_ == kFrameRate) {
            frame_index_ = (frame_index_ + 1) % textures_.size();
            frame_rate_ = 0;
        }
        frame_rate_++;
    }

    ci::gl::Texture2dRef Bird::GetTexture() const {
        return textures_[frame_index_];
    }

    int Bird::GetTop() const {
        return position_.y - height_ / 2;
    }

    int Bird::GetBottom() const {
        return position_.y + height_ / 2;
    }

    int Bird::GetRight() const {
        return position_.x + width_ / 2;
    }

    int Bird::GetLeft() const {
        return position_.x - width_ / 2;
    }

    void Bird::SetPosition(const vec2 setPosition) {
        if (setPosition.y < display_bottom_ - height_ / 2 &&
            setPosition.y > display_top_ + height_ / 2) {
            position_ = setPosition;
        }
    }
}  //namespace flappybird