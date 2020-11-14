#pragma once
#include "Initial.h"
#include "Collider.h"
#include "Animation.h"
#include "Player.h"
#include "Bullet.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount,sf::Vector2f position ,float switchTime,int type,int randomInt);
	~Enemy();

	void Update( float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void hitWithBullet(Bullet &bullet);
	void spawnBox();
	void alreadySpawnBox(bool isAlreadySpawnBoxBool);

	int getSpawnBoxInt() { return randomInt; }
	bool isAlreadySpawnBox(){ return isAlreadySpawnBoxBool; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isDead() { return isDeadBool; }
	float getHp() { return hp; }
	bool isSpawnBox() { return spawnBoxBool;  }

private:
	sf::RectangleShape body;
	Animation animation;

	int randomInt;
	int randomInt2;
	int typeOfBullet;
	bool spawnBoxBool;
	bool isAlreadySpawnBoxBool;
	bool faceRight;
	bool isHit;
	bool isDeadBool;
	bool isOnGround;
	float speed;
	float hp;
	float delayTime;
	sf::Vector2f velocity;

};

