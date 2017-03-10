#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 140 , 0, 255)))
    {
        return false;
    }

	auto menuTitle =
		MenuItemImage::create("MainMenuScreen/Title.png",
		"MainMenuScreen/Title.png");
	auto playItem =
		MenuItemImage::create("MainMenuScreen/Play_Button.png",
		"MainMenuScreen/Play_Button(Click).png",
		CC_CALLBACK_1(MainMenu::activateGameScene, this));
	auto exitItem =
		MenuItemImage::create("MainMenuScreen/Exit_Button.png",
		"MainMenuScreen/Exit_Button(Click).png",
		CC_CALLBACK_1(MainMenu::exitGame, this));
	auto menu = Menu::create(menuTitle, playItem, exitItem, NULL);

	// Returns visible size of OpenGL window in points.
	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 20);
	this->addChild(menu);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MenuMusic.wav", true);

    return true;
}

void MainMenu::exitGame(Ref* pSender)
{
	CCDirector::sharedDirector()->end();
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::activateGameScene(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("MenuMusic.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameMusic.wav", true);
}

