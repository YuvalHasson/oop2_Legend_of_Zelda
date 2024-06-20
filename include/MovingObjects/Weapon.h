#pragma once

#include "MovingObjects.h"


class Weapon : public MovingObjects {
public:
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void handleCollision() = 0;
    virtual void deActivate() = 0;
    virtual bool getActive()const = 0;
    virtual void setActive(bool active) = 0;
    virtual const sf::Vector2u& getAnimationTexturePosition(Input) = 0;
};