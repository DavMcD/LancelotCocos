#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto pauseItem = MenuItemImage::create("GameScreen/Pause_Button.png",
		"GameScreen/Pause_Button(Click).png", CC_CALLBACK_1(GameScene::activatePauseScene, this));

	//player controls
	auto upBut =
		MenuItemImage::create("GameScreen/SpeedUpButton.png",
		"GameScreen/SpeedUpButtonclicked.png",
		CC_CALLBACK_0(GameScene::speedUp1, this));
	auto downBut =
		MenuItemImage::create("GameScreen/SpeedDownButton.png",
		"GameScreen/SpeedDownButtonclicked.png",
		CC_CALLBACK_0(GameScene::speedDown1, this));
	auto lAtkBut =
		MenuItemImage::create("GameScreen/LightAttackButton.png",
		"GameScreen/LightAttackButtonclicked.png",
		CC_CALLBACK_0(GameScene::lightAtk1, this));
	auto mAtkBut =
		MenuItemImage::create("GameScreen/MedAttackButton.png",
		"GameScreen/MedAttackButtonclicked.png",
		CC_CALLBACK_0(GameScene::midAtk1, this));
	auto hAtkBut =
		MenuItemImage::create("GameScreen/HeavyAttackButton.png",
		"GameScreen/HeavyAttackButtonclicked.png",
		CC_CALLBACK_0(GameScene::heavyAtk1, this));
	auto guardBut =
		MenuItemImage::create("GameScreen/GuardButton.png",
		"GameScreen/GuardButtonclicked.png",
		CC_CALLBACK_0(GameScene::guard1, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	upBut->setPosition(Vec2(100, 130));
	downBut->setPosition(Vec2(100, 50));
	lAtkBut->setPosition(Vec2(900, 50));
	mAtkBut->setPosition(Vec2(900, 130));
	hAtkBut->setPosition(Vec2(1000, 130));
	guardBut->setPosition(Vec2(1000, 50));

	pauseItem->setPosition(Point(pauseItem->getContentSize().width -
		(pauseItem->getContentSize().width / 10) + origin.x,
		visibleSize.height - pauseItem->getContentSize().height +
		(pauseItem->getContentSize().width / 10) + origin.y));

	auto gameButtons = Menu::create(pauseItem, upBut, downBut, lAtkBut, mAtkBut, hAtkBut, guardBut, NULL);
	gameButtons->setPosition(Point::ZERO);
	this->addChild(gameButtons, 8);

	player = Player::create();
	player->setPosition(Vec2(700, 275));
	this->addChild(player, 5);

	player2 = Player2::create();
	player2->setPosition(Vec2(200, 325));
	this->addChild(player2, 5);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	label1 = Label::create("Player 1 Health", "Arial", 40);
	label2 = Label::create("Player 2 Health", "Arial", 40);
	labelHealth1 = Label::create("100", "Arial", 40);
	labelHealth2 = Label::create("100", "Arial", 40);

	label1->setPosition(200, winSize.height - 100);
	label2->setPosition(1000, winSize.height - 100);
	labelHealth1->setPosition(200, winSize.height - 150);
	labelHealth2->setPosition(1000, winSize.height - 150);
	// add this to the layer
	this->addChild(label1, 6);
	this->addChild(label2, 6);
	this->addChild(labelHealth1, 6);
	this->addChild(labelHealth2, 6);

	guardSprite = cocos2d::Sprite::create("GameScreen/shieldIcon.png");
	this->addChild(guardSprite, 10);

	HAttkprite = cocos2d::Sprite::create("GameScreen/Hvy.png");
	this->addChild(HAttkprite, 10);

	LAttkSprite = cocos2d::Sprite::create("GameScreen/Lance.png");
	this->addChild(LAttkSprite, 10);

	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameScene::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

}

//function calls for controling player
void GameScene::speedUp1()
{
	player->speedUp();
}
void GameScene::speedDown1()
{
	player->speedDown();
}
void GameScene::lightAtk1()
{
	player->attack(1);
	if (player->getDir() < 0)
	{
		LAttkSprite->setPosition(Vec2(player->getPositionX() + 212, player->getPositionY()));
	}
}
void GameScene::midAtk1()
{
	player->attack(2);
	if (player->getDir() < 0)
	{
		LAttkSprite->setPosition(Vec2(player->getPositionX() + 212, player->getPositionY()));
	}
}
void GameScene::heavyAtk1()
{
	player->attack(3);
	if (player->getDir() < 0)
	{
		LAttkSprite->setPosition(Vec2(player->getPositionX() + 212, player->getPositionY()));
	}
}
void GameScene::guard1()
{
	guardSprite->setPosition(Vec2(player->getPositionX(), player->getPositionY()));
}

//function calls for controling player2
void GameScene::speedUp2()
{
}
void GameScene::speedDown2()
{
}
void GameScene::lightAtk2()
{
}
void GameScene::midAtk2()
{
}
void GameScene::heavyAtk2()
{
}
void GameScene::guard2()
{
}

void GameScene::update(float dt)
{
	timer++;
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	player->update(this);
	player2->update(this);

	if (player->getDamaging() == false)
	{
		LAttkSprite->setPosition(Vec2(-1000, -1000));
	}


	if (player->getDamaging())
	{

		if (player->getDir() > 0)
		{
			if (player->getPositionX() + 212 > player2->getPositionX()
				&& player->getPositionX() + (100 * player->getAtkType()) < player2->getPositionX())
			{
				player2->loseLives();
			}
		}
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	//get location of my touch event for player movement
	float x = touch->getLocation().x - player->getPosition().x;
	float y = touch->getLocation().y - player->getPosition().y;
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x /= magnitude;
	y /= magnitude;

	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
}

void GameScene::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("GameMusic.wav");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bossHit.wav");
}

void GameScene::activateGameOverScene(Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	return true;
}