#pragma once
#include "Initial.h"
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime,float speed,float jumpHeight);
	~Player();

	void Update(sf::Texture* texture,float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void setGunType(int gunType);

	int GetGunType() { return gunType; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isFaceRight() { return faceRight; }
	bool isShooting() { return shootingBool; }
	float getShootDelayTime() { return delayShoot; }
	float getHp() { return hp; }

private:
	sf::RectangleShape body;
	Animation animation;
	float speed;
	bool  faceRight;
	bool shootingBool;

	float hp;
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	float delayShoot;
	int gunType;
};

