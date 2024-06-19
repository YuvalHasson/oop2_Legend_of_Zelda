#pragma once

#include "Weapon.h"


class EnemySword.h : public Weapon {
public:
    virtual void update(const sf::Time& deltaTime) override;
    virtual void handleCollision() override;
    virtual void deActivate() override;
    virtual bool getActive()const override;
    virtual void setActive(bool active) override;
    virtual const sf::Vector2u& getAnimationTexturePosition(Input) override;
};