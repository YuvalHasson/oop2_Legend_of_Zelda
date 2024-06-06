#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"


//animation class is based on image of animation being in same row and seperated by 1 pixel
//start position is the true top left of the the first image
//image count is unsigned for how many images are in the animation
class Animation{
public:
    Animation(sf::Vector2u startPosition, int imageCount, float switchTime, int spriteWidth = tileSize, int spriteHeight = tileSize);

    void update(const sf::Time& deltaTime, bool flip = false);

    //for when changing animation for an object
    //i.e if link has a shield or not
    void setStartPoisition(sf::Vector2u);
    void setImageCount(int);

    //returns the correct rect to use with the sprite
    sf::IntRect getuvRect()const;


private:
    sf::Vector2u m_animationStartPosition;//(x,y) in pixels for start position for specific animation
    int m_imageCount; //(x,y) x- how many rows of images, y- how many images in a row
    int m_currentImage;

    sf::IntRect m_uvRect;
    bool m_singleImgFlip;

    float m_timePassed;//time passed from last image change
    float m_switchTime; //switch interval between each picture

};