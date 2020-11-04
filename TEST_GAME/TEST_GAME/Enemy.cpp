#include "Enemy.h"
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int type):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->isDeadBool = false ;
	this->spawnBoxBool = false;
	srand(time(NULL));
	int ran=rand();
	if (ran%2 == 1) {
		velocity.x = speed;
		faceRight = true;
	}
	else {
		faceRight = false;
		velocity.x = -(speed);
	}

	switch (type) {
	case 1: 
		this->hp=150.0f;
		body.setSize(sf::Vector2f(30.0f, 36.0f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(540.0f, 0.0f);
		body.setTexture(texture);
		break;  
	}
}

Enemy::~Enemy()
{
}
int temp=30;
float tempSpeed;
void Enemy::Update( float deltaTime)
{
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
	if (isHit == true) {
		if (velocity.x != 0.0f) {
			tempSpeed = velocity.x;
		}
		if (temp > 0) {
			body.setFillColor(sf::Color(255, 0, 0));
			temp -= 1;
		}
		else {
			body.setFillColor(sf::Color(255, 255, 255));
			isHit = false;
			temp = 30;
		}
		if (isOnGround) {
			switch (typeOfBullet) {
				case 0:
					if (temp > 0) {
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
					body.move(-velocity*1.50f* deltaTime);
					animation.Update(deltaTime, faceRight);
					body.setTextureRect(animation.uvRect);
			}

		}
	}
	else {
		animation.Update(deltaTime, faceRight);
		body.setTextureRect(animation.uvRect);
		body.move(velocity * deltaTime);
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
{

	//std::cout << "Direction " << direction.x << std::endl;
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

	//std::cout << velocity.x << " " << velocity.y << std::endl;
}

void Enemy::hitWithBullet(Bullet& bullet)
{
	hp-=bullet.GetDamage();
	this->typeOfBullet = bullet.GetType();
	this->isHit = true;
}

void Enemy::spawnBox()
{
	srand(time(NULL));
	int ran = rand();
	switch (ran % 20) {
		case 0:
		case 5:
		case 4:
		case 6:
		case 11:
			this->spawnBoxBool = true;
			break;
	}
}
