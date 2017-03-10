#include "Player.h"
USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();

	if (player && player->initWithFile("GameScreen/Player1.png", Rect(0, 0, 212, 48)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(6);
		char str[100] = { 0 };
		for (int i = 0; i < 6; i++)
		{
			sprintf(str, "GameScreen/Player1.png");
			auto frame = SpriteFrame::create(str, Rect(0, 48 * i, 212, 48));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(212, 48);
		player->runAction(animate);
		player->initPlayer();
		player->setTag(10);
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::move(float x, float y)
{
	dirX = x;
	dirY = y;
	moving = true;
}

void Player::attack(byte atkNum)
{
	atkType = atkNum;
	if (atkNum == 1)
	{
		counter = 7;
	}
	else if (atkNum == 2)
	{
		counter = 7;
	}
	else if (atkNum == 3)
	{
		counter = 7;
	}
}

float Player::getLives(){
	return lives;
}

float Player::setLives(){
	lives = 10;
	return lives;
}

void Player::update(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	setPositionX(getPosition().x - dirX * speed);

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
	if (counter > 0)
	{
		counter--;
	}
	if (counter <= 6 && counter > 0)
	{
		damaging = true;
	}
	if (counter == 0)
	{
		damaging = false;
	}
}

bool Player::movingTrue() {
	canMove = true;
	return canMove;
}

bool Player::getDamaging() {
	return damaging;
}

short Player::getAtkType() {
	return atkType;
}

float Player::getDir() {
	return dirX;
}

void Player::loseLives() {
	lives --;
}

void Player::idle() {
	moving = false;
}

void Player::initPlayer() {
	speed = 1.f;
	lives = 10;
	dirX = dirY = 5;
}

void Player::speedDown() {
	if (speed >0.5f){
		speed -= 0.5f;
	}
}

void Player::speedUp() {
	if (speed <2) {
		speed += 0.5f;
	}
}

