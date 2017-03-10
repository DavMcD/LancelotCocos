#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameScene.h"
#include "GameStates.h"

class Player2 : public cocos2d::Sprite{
public:
	static Player2 * create(void);
	void initBullet();
	void update(GameScene* world);
	bool getRemove();
	void move(float x, float y);
	void animateBullet();
	bool movingTrue();
	void loseLives();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;
	float dirX, dirY;
	float speed;
	float lives = 10;
	bool canMove = false;
};