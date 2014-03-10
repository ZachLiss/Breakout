#include "HelloWorldScene.h"
#include "Game.h"
#include "Options.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
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
    
    UserDefault::getInstance()->setBoolForKey("sound", true);
    
    auto label = LabelTTF::create("FREAKOUT! - Zach Liss", "Arial", 50);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // create menue items
    auto newGame = MenuItemFont::create("New Game", CC_CALLBACK_1(HelloWorld::menuNewGame, this));
    auto options = MenuItemFont::create("Options", CC_CALLBACK_1(HelloWorld::menuOptions, this));
    
    // set coordinates
    newGame->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    options->setPosition(Point(visibleSize.width/2 + origin.x, (visibleSize.height/2 + origin.y) - (2 * newGame->getContentSize().height)));
    
    auto mainMenu = Menu::create(newGame, options, NULL);
    mainMenu->setPosition(Point::ZERO);
    this->addChild(mainMenu);

    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuNewGame(Object* p) {
    // create a new game Scene
    auto gameScene = Game::createScene();
    Director::getInstance()->pushScene(gameScene);
}

void HelloWorld::menuOptions(Object* p) {
    // create a new options Scene
    auto o = Options::createScene();
    Director::getInstance()->pushScene(o);
    
}
