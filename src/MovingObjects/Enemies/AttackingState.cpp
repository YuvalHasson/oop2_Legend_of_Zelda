//#include "AttackingState.h"
//#include "Utilities.h"
//#include "PigWarrior.h"
//#include <iostream>
//
//AttackingState::AttackingState() : m_attackDuration(sf::seconds(0.3f)), m_isAnimationSet(false) {}
//
//std::unique_ptr<MovementStrategy> AttackingState::handleInput(Input input) 
//{
//    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0) {
//        return std::make_unique<StandingState>();
//    }
//    return nullptr;
//}
//
//void AttackingState::enter(MovingObjects& obj) {
//    m_attackTimer.restart();
//    sf::Vector2i currentDirection = obj.getDirection();
//    if (!m_isAnimationSet) {
//        if (currentDirection == DIRECTIONS::Right || currentDirection == DIRECTIONS::UpRight || currentDirection == DIRECTIONS::DownRight) {
//            obj.setGraphics(obj.getAnimationTexturePosition(PRESS_RIGHT), 2);
//        }
//        else if (currentDirection == DIRECTIONS::Left || currentDirection == DIRECTIONS::UpLeft || currentDirection == DIRECTIONS::DownLeft) {
//            obj.setGraphics(obj.getAnimationTexturePosition(PRESS_LEFT), 2);
//        }
//        else if (currentDirection == DIRECTIONS::Down) {
//            obj.setGraphics(obj.getAnimationTexturePosition(PRESS_DOWN), 2);
//        }
//        else if (currentDirection == DIRECTIONS::Up) {
//            obj.setGraphics(obj.getAnimationTexturePosition(PRESS_UP), 2);
//        }
//        //std::cout << "in attacking\n";
//        obj.setAttacking(true);
//    }
//    if (dynamic_cast<PigWarrior*>(&obj))
//    {
//        //std::cout << "before swipe sword\n";
//        dynamic_cast<PigWarrior*>(&obj)->swipeSword();
//        //std::cout << "after swipe sword\n";
//    }
//}