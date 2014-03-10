//
//  Game.h
//  Breakout
//
//  Created by Zach Liss on 3/2/14.
//
//

#ifndef __Breakout__Game__
#define __Breakout__Game__

#include <iostream>
#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    
    // move the ball
    void moveBall(float dt);
    
    void gameWon();
    void gameLost();
    void createMenu();
    void menuPlayAgain(Object* p);
    void menuMainMenu(Object* p);
    
    cocos2d::Vector<cocos2d::Sprite *> _bricks;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};


#endif /* defined(__Breakout__Game__) */
