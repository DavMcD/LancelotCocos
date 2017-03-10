#pragma once

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "GameData.h"


#include "SimpleAudioEngine.h"  

#include <string>
#include <iostream>

class Player;
class Player2;

class GameScene : public cocos2d::Layer
{
private:
	

	Player* player;
	Player2* player2;

	cocos2d::Label *label1;
	cocos2d::Label *label2;
	cocos2d::Label *labelHealth1;
	cocos2d::Label *labelHealth2;

	cocos2d::Sprite* guardSprite;
	cocos2d::Sprite* HAttkprite;
	cocos2d::Sprite* LAttkSprite;

	int timer = 0;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
    
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene(Ref *pSender);
	void update(float dt);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	void speedUp1();
	void speedDown1();
	void lightAtk1();
	void midAtk1();
	void heavyAtk1();
	void guard1();

	void speedUp2();
	void speedDown2();
	void lightAtk2();
	void midAtk2();
	void heavyAtk2();
	void guard2();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#include "Player.h"
#include "Player2.h"