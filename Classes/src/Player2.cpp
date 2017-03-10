#include "Player2.h"

USING_NS_CC;

Player2 * Player2::create()
{
	Player2 * player2 = new Player2();

	if (player2 && player2->initWithFile("GameScreen/Player2.png", Rect(0, 0, 212, 48)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(6);
		char str[100] = { 0 };
		for (int i = 0; i < 6; i++)
		{
			sprintf(str, "GameScreen/Player2.png");
			auto frame = SpriteFrame::create(str, Rect(0, 48 * i, 212, 48));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(212, 48);
		player2->runAction(animate);
		player2->initBullet();
		player2->setTag(20);
		return player2;
	}
	CC_SAFE_DELETE(player2);
	return NULL;
}

void Player2::animateBullet()
{

}

void Player2::move(float x, float y)
{
	dirX = x;
	dirY = y;
}

void Player2::loseLives(){
	lives--;
}

bool Player2::getRemove(){
	return remove;
}

void Player2::initBullet(){
	timecounter = timeAlive = 0;
	remove = false;
	dirX = 5;
	speed = 1.f;
}

void Player2::update(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	setPositionX(getPosition().x + dirX * speed);

	if (getPositionX() > s.width - 20)
	{
		dirX = dirX * -1;
		setRotation(getRotation() + 180);
	}
	if (getPositionX() < 20)
	{
		dirX = dirX * -1;
		setRotation(getRotation() + 180);
	}
}

bool Player2::movingTrue() {
	canMove = true;
	return canMove;
}