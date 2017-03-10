#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"
#include "Player2.h"

class Player : public cocos2d::Sprite{
public:
	static Player * create(void);

	void move(float x, float y);
	void update(GameScene* world);
	void idle();
	void loseLives();
	void speedDown();
	void speedUp();
	void attack(byte atkNum);

	float getLives();
	float setLives();

	bool movingTrue();
	bool getDamaging();
	short getAtkType();
	float getDir();

private:
	void initPlayer();

	float dirX, dirY;
	float speed;
	float lives = 10;

	bool moving;
	bool hit;
	bool attacking;
	bool damaging=false;
	short atkType;

	short counter = 0;
	const short SECOND = 60;

	bool canMove = false;
};