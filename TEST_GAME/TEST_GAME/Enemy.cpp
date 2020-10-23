#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int type):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	srand(time(NULL));
	int ran=rand();
	printf("ran = %d", ran);
	if (ran%2 == 1) {
		velocity.x = speed;
		faceRight = true;
	}
	else {
		faceRight = false;
		velocity.x = -(speed);
	}
	std::cout << "FaceRight "<<faceRight << std::endl;

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

void Enemy::Update( float deltaTime)
{	
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
	animation.Update(deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity*deltaTime);
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
	}

	//std::cout << velocity.x << " " << velocity.y << std::endl;
}

void Enemy::hitWithBullet(Bullet& bullet)
{
	hp-=bullet.GetDamage();
	
	printf("Hit");
	if (hp <= 0) {
		isDeadBool = true;
	}
}
