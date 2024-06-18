#include "Animation.h"
#include <iostream>

Animation::Animation(): m_singleImgFlip(false), m_flip(false), m_timePassed(0),
     m_switchTime(0.17f), m_singleTime(false){
    m_uvRect.width = tileSize;
    m_uvRect.height = tileSize;
}

Animation::Animation(sf::Vector2u startPosition ,int imageCount, float switchTime, int spriteWidth, int spriteHeight)
    : m_animationStartPosition(startPosition), m_imageCount(imageCount), m_currentImage(0),
     m_singleImgFlip(true),m_timePassed(0),m_switchTime(switchTime), m_singleTime(false){
    
    m_uvRect.top = startPosition.y;
    m_uvRect.left = startPosition.x;

    m_uvRect.width = spriteWidth;
    m_uvRect.height = spriteHeight;
}

//flip is to mirror image according to x value
void Animation::update(const sf::Time& deltaTime) {
    
    m_timePassed += deltaTime.asSeconds();

    if(m_singleTime && m_currentImage >= m_imageCount - 1){
        return;
    }
    //if only a single image is to be drawn it will be flipped with each time interval
    if (m_imageCount == 1) {
        if (m_timePassed >= m_switchTime) {
            m_timePassed -= m_switchTime;

            m_uvRect.width = -m_uvRect.width;
            m_uvRect.left = m_animationStartPosition.x + abs(m_uvRect.width) * m_singleImgFlip;

            m_singleImgFlip = ! m_singleImgFlip;
        }
    }
    else{

        if (m_timePassed >= m_switchTime) {
            m_timePassed -= m_switchTime;
            
            m_currentImage++;

            if (m_currentImage >= m_imageCount && !m_singleTime) {
                m_currentImage = 0;
            }
        }
        if (m_flip) {
            m_uvRect.left = m_animationStartPosition.x + ((m_currentImage + 1) * abs(m_uvRect.width)) + (1 * m_currentImage);
            m_uvRect.width = -abs(m_uvRect.width);
        } 
        else {
            m_uvRect.left = m_animationStartPosition.x + m_currentImage * m_uvRect.width + (1 * m_currentImage);
            m_uvRect.width = abs(m_uvRect.width);
        }
    }

    m_uvRect.top = m_animationStartPosition.y;
}

void Animation::setAnimation(sf::Vector2u startPosition, int imgCount, bool flip, bool singleTime, float switchTime){
    if(m_animationStartPosition == startPosition){
        if(singleTime){
            m_currentImage = 0;
            m_timePassed = 0;
        }
        return;
    }
    m_animationStartPosition = startPosition;
    m_currentImage = 0;
    m_timePassed = 0;
    m_imageCount = imgCount;
    m_uvRect.left = startPosition.x;
    m_uvRect.top = startPosition.y;
    m_flip = flip;
    m_singleTime = singleTime;
    m_switchTime = switchTime;
}

sf::IntRect Animation::getuvRect()const{
    return m_uvRect;
}

bool Animation::isDone()const{
    return m_singleTime && m_currentImage >= m_imageCount - 1;
}