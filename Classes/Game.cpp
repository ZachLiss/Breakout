//
//  Game.cpp
//  Breakout
//
//  Created by Zach Liss on 3/2/14.
//
//

#include <cmath>
#include "Game.h"
#include "HelloWorldScene.h"
#include "Options.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Vector<cocos2d::Sprite *> _bricks;
LabelTTF *score;
Sprite *ball, *paddle;
Size visibleSize;
Point origin;
bool startGame;
bool sound;
int bricksHit;
float xVector;
float yVector;
float touchX;
float touchY;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
//    auto label = LabelTTF::create("Playing a game now!!!", "Arial", 50);
//    
//    // position the label on the center of the screen
//    label->setPosition(Point(origin.x + visibleSize.width/2,
//                             origin.y + visibleSize.height - label->getContentSize().height));
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
    
    score = LabelTTF::create("Score: 0", "Arial", visibleSize.height / 25);
    score->setPosition(Point(visibleSize.width - visibleSize.width / 20, origin.y + 3 * score->getContentSize().height));
    this->addChild(score);
    
    sound = UserDefault::getInstance()->getBoolForKey("sound");
    startGame = false;
    bricksHit = 0;

    
    ball = Sprite::create("ball.png");
    ball->setScale(1.0 / ((15.0 * ball->getContentSize().height) / visibleSize.height), 1.0 / ((15.0 * ball->getContentSize().width) / visibleSize.height));
    ball->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    paddle = Sprite::create("paddle.png");
    paddle->setScale(1.0 / ((30.0 * paddle->getContentSize().height) / visibleSize.height), 1.0 / ((6.0 * paddle->getContentSize().width) / visibleSize.width));
    paddle->setPosition(Point(visibleSize.width/2 + origin.x, origin.y + 1.5*paddle->getContentSize().height ));
    
    // create 1st row of bricks
    for(int i = 1; i < 6; i++) {
        auto b = Sprite::create("brick.png");
        float w = b->getContentSize().width;
        b->setScale(1.0 / ((6.0 * w) / visibleSize.width), 1.0 / ((15.0 * b->getContentSize().height) / visibleSize.height));
        b->setPosition(Point(i * visibleSize.width / 6, visibleSize.height - b->getContentSize().height));
        this->_bricks.pushBack(b);
        this->addChild(b);
    }
    
    // create 2nd row of bricks
    for(int i = 1; i < 6; i++) {
        auto b = Sprite::create("brick.png");
        float w = b->getContentSize().width;
        b->setScale(1.0 / ((6.0 * w) / visibleSize.width), 1.0 / ((15.0 * b->getContentSize().height) / visibleSize.height));
        b->setPosition(Point(i * visibleSize.width / 6, visibleSize.height - 2.0*b->getContentSize().height));
        this->_bricks.pushBack(b);
        this->addChild(b);
    }
    
    
    this->addChild(ball);
    this->addChild(paddle);
    
    // set initial vectors
    xVector = 0.0;
    yVector = - visibleSize.height / 2;
    
    this->schedule(schedule_selector(Game::moveBall));
    
    // Register Touch Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void Game::moveBall(float dt) {
    if(startGame) {
        ball->setPosition(Point(ball->getPositionX() + xVector * dt, ball->getPositionY() + yVector * dt));
        auto ballRect = ball->getBoundingBox();
        
        // check perimeter collison
        if( (ball->getPositionX() > (visibleSize.width - (ball->getContentSize().width / 2))) || (ball->getPositionX() < origin.x + (ball->getContentSize().width / 2)) ) {
            xVector = -xVector;
        } else if( (ball->getPositionY() > (visibleSize.height - (ball->getContentSize().height / 2)))/* || (ball->getPositionY() < origin.y + (ball->getContentSize().height / 2))*/) {
            yVector = -yVector;
        }
        
        // check paddle collision
        auto paddleRect = paddle->getBoundingBox();
        
        if (ballRect.intersectsRect(paddleRect)) {
            yVector = -yVector;
            float dif = abs(ball->getPositionX() - paddle->getPositionX());
            if(ball->getPositionX() < paddle->getPositionX()) {
                xVector = xVector -2.5*dif;
            } else {
                xVector = xVector + 2.5*dif;
            }
            if(sound){
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("paddle-bounce.wav");
            }
        }
        
        
        // check brick collision
        for(auto brick : this->_bricks) {
            auto brickRect = brick->getBoundingBox();
            if(ballRect.intersectsRect(brickRect)) {
                brick->setVisible(false);
                _bricks.eraseObject(brick);
                yVector = -yVector;
                bricksHit++;
                char ss[256];
                sprintf(ss, "Score: %d", bricksHit);
                score->setString(ss);
                if(sound) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("brick-bounce.wav");
                }
            }
        }
        
        if(bricksHit == 10) {
            Game::gameWon();
        }
        
        if(ball->getPositionY() < origin.y) {
            Game::gameLost();
        }
    }
    
}

void Game::gameWon() {
    Director::getInstance()->pause();
    auto label = LabelTTF::create("YOU WON!!!", "Arial", visibleSize.height / 15);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - 3 * label->getContentSize().height ));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    Game::createMenu();
}

void Game::gameLost() {
    Director::getInstance()->pause();
    auto label = LabelTTF::create("YOU LOSE :(", "Arial", visibleSize.height / 15);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - 3 * label->getContentSize().height ));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    Game::createMenu();
}

void Game::createMenu() {
    auto playAgain = MenuItemFont::create("Play Again", CC_CALLBACK_1(Game::menuPlayAgain, this));
    auto mm = MenuItemFont::create("Main Menu", CC_CALLBACK_1(Game::menuMainMenu, this));
    
    // set coordinates
    playAgain->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    mm->setPosition(Point(visibleSize.width/2 + origin.x, (visibleSize.height/2 + origin.y) - (2 * playAgain->getContentSize().height)));
    
    auto mainMenu = Menu::create(playAgain, mm, NULL);
    mainMenu->setPosition(Point::ZERO);
    this->addChild(mainMenu);
}

void Game::menuPlayAgain(Object* p) {
    // resume and restart the game
    startGame = false;
    auto gameScene = Game::createScene();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(gameScene);
}

void Game::menuMainMenu(Object* p) {
    // pop scene and go back to main menu
    startGame = false;
    Director::getInstance()->resume();
    Director::getInstance()->popScene();
}

bool Game::onTouchBegan(Touch *touch, Event *unused_event) {
   // yVector = yVector + 10;
    touchX = touch->getLocation().x;
    startGame = true;
    return true;
}

void Game::onTouchMoved(Touch *touch, Event *unused_event) {
    if(paddle->getPositionX() < visibleSize.width || paddle->getPositionX() > origin.x) {
        paddle->setPosition(paddle->getPositionX() + (touch->getLocation().x - touchX), paddle->getPositionY());
    }
    touchX = touch->getLocation().x;
}

void Game::onTouchEnded(Touch *touch, Event *unused_event) {
}



