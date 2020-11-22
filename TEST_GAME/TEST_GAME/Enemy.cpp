#include "Enemy.h"
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount,sf::Vector2f position,float switchTime,int type,int randomInt):
	animation(texture, imageCount, switchTime)
{
	srand(randomInt);
	randomInt2 = rand();
	this->timeAliveClock.restart();
	this->isHitBool = false;
	this->timeAlive = 0.0f;
	this->isAlreadySpawnBoxBool = false;
	switch (randomInt%3) {
		case 0:
			this->speed = 140.0f;
			break;
		case 1:
			this->speed = 145.0f;
			break;
		case 2:
			this->speed = 150.0f;
			break;
	}
	this->isDeadBool = false ;
	this->spawnBoxBool = false;
	this->randomInt = randomInt;
	if (randomInt%2 == 1) {
		velocity.x = speed;
		faceRight = true;
	}
	else {
		faceRight = false;
		velocity.x = -(speed);
	}
	switch (type) {
	case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 9:case 8:
			this->hp=150.0f;
			body.setSize(sf::Vector2f(30.0f, 36.0f));
			body.setOrigin(body.getSize() / 2.0f);
			body.setPosition(position);
			body.setTexture(texture);
			this->type = 0;
			this->score = 50;
			this->dmg = -1;
			break;  
		case 2: 
			this->hp = 450.0f;
			this->speed = 115.0f;
			body.setSize(sf::Vector2f(54.0f, 64.8f));
			body.setOrigin(body.getSize() / 2.0f);
			body.setPosition(position);
			body.setTexture(texture);
			this->type = 1;
			this->score = 1500;
			this->dmg = -2;
			break;
	}
}

Enemy::~Enemy()
{
}
float tempSpeed;
void Enemy::Update( float deltaTime)
{
	timeAlive = timeAliveClock.getElapsedTime().asMilliseconds();
	isOnGround = false;
	if (this->hp <= 0) {
		isDeadBool = true;

	}
	if (velocity.x < 0) {
		faceRight = false;
	}
	else if (velocity.x > 0) {
		faceRight = true;
	}
	velocity.y += 981.0f * deltaTime;
	if (velocity.y > 10000) {
		velocity.y = 981.0f;
	}
	if (isHitBool == true) {
		if (velocity.x != 0.0f) {
			tempSpeed = velocity.x;
		}
		if (timeAlive-delayTime < 70) {
			body.setFillColor(sf::Color(255, 0, 0));
		}
		else {
			body.setFillColor(sf::Color(255, 255, 255));
			isHitBool = false;
			delayTime = 0;
		}
		if (isOnGround) {
			switch (typeOfBullet) {
			case 0:
				if (timeAlive - delayTime < 70) {
					velocity.x = 0.0f;
				}
				else {
					velocity.x = tempSpeed;
				}
			case 1:
				body.move(-velocity * deltaTime);
				animation.Update(deltaTime, faceRight);
				body.setTextureRect(animation.uvRect);
			case 2:
				body.move(-velocity * 1.50f * deltaTime);
				animation.Update(deltaTime, faceRight);
				body.setTextureRect(animation.uvRect);
			}

		}
	}
	else if(!isDeadBool){
		animation.Update(deltaTime, faceRight);
		body.setTextureRect(animation.uvRect);
		body.move(velocity * deltaTime);
	}
	else if (!isDeadBool && !isHitBool) {
		body.setTextureRect(animation.uvRect);
		body.move(velocity * deltaTime);
	}
	else if (isDeadBool) {
		velocity.x = 0.0f;
		if (faceRight) {
			body.rotate(-45.0f);
		}
		else {
			body.rotate(45.0f);
		}
		body.move(velocity * deltaTime);
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
{

	if (direction.x < 0.0f) {
		velocity.x = -1*speed;
	}
	else if (direction.x > 0.0f) {
		velocity.x =  speed;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		isOnGround = true;
	}

}

void Enemy::hitWithBullet(Bullet& bullet)
{
	delayTime = timeAliveClock.getElapsedTime().asMilliseconds();
	hp-=bullet.GetDamage();
	this->typeOfBullet = bullet.GetType();
	this->isHitBool = true;
}

void Enemy::spawnBox()
{
	switch ((this->randomInt + randomInt2) % 18) {
		case 0:
		case 5:
		case 4:
		case 6:
		case 11:
		case 12:
		case 16:
			this->spawnBoxBool = true;
			break;
	}
	if (this->type == 1) {
		this->spawnBoxBool = true;
	}
}

void Enemy::alreadySpawnBox(bool isAlreadySpawnBoxBool)
{
	this->isAlreadySpawnBoxBool = isAlreadySpawnBoxBool;
}
