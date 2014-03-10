//
//  Options.h
//  Breakout
//
//  Created by Zach Liss on 3/5/14.
//
//

#ifndef __Breakout__Options__
#define __Breakout__Options__

#include <iostream>
#include "cocos2d.h"

class Options : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Options);
    
    void menuSoundFXOn(Object* p);
    void menuSoundFXOff(Object* p);
    void menuBack(Object* p);
};


#endif /* defined(__Breakout__Options__) */
