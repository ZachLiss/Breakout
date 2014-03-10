//
//  Options.cpp
//  Breakout
//
//  Created by Zach Liss on 3/5/14.
//
//

#include "Options.h"
#include "Game.h"
#include "HelloWorldScene.h"

USING_NS_CC;


Scene* Options::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Options::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Options::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Options::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("OPTIONS!", "Arial", 50);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);

    
    // time to try some touch stuff
    // create menue items
    auto soundFXOn = MenuItemFont::create("Sound FX ON", CC_CALLBACK_1(Options::menuSoundFXOn, this));
    auto soundFXOff = MenuItemFont::create("Sound FX OFF", CC_CALLBACK_1(Options::menuSoundFXOff, this));
    auto back = MenuItemFont::create("Main Menu", CC_CALLBACK_1(Options::menuBack, this));
    
    // set coordinates
    soundFXOn->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    soundFXOff->setPosition(Point(visibleSize.width/2 + origin.x, (visibleSize.height/2 + origin.y) - (2 * soundFXOn->getContentSize().height)));
    back->setPosition(Point(visibleSize.width / 2 + origin.x, (visibleSize.height / 2 + origin.y) - (4 * soundFXOn->getContentSize().height)));
    
    auto mainMenu = Menu::create(soundFXOn, soundFXOff, back, NULL);
    mainMenu->setPosition(Point::ZERO);
    this->addChild(mainMenu);
    
    
    return true;
}


void Options::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->popScene();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Options::menuSoundFXOn(Object* p) {
    // turn on sound effects
    UserDefault::getInstance()->setBoolForKey("sound", true);
}

void Options::menuSoundFXOff(Object* p) {
    // turn off sound effects
    UserDefault::getInstance()->setBoolForKey("sound", false);
    
}

void Options::menuBack(Object* p) {
    // back to the main menu
    Director::getInstance()->popScene();
}





