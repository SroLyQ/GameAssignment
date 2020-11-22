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

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isDead() { return isDeadBool; }
	bool isSpawnBox() { return spawnBoxBool;  }
	bool isAlreadySpawnBox(){ return isAlreadySpawnBoxBool; }
	bool isHit() { return isHitBool; }
	float getHp() { return hp; }
	int getTimeAlive() { return timeAlive; }
	int getSpawnBoxInt() { return randomInt; }
	int getType() { return type; }
	int getScore() { return score; }
	int getDmg() { return dmg; }

private:
	sf::RectangleShape body;
	sf::Clock timeAliveClock;
	Animation animation;

	int randomInt;
	int randomInt2;
	int typeOfBullet;
	int type;
	int score;
	int timeAlive;
	int dmg;
	bool spawnBoxBool;
	bool isAlreadySpawnBoxBool;
	bool faceRight;
	bool isHitBool;
	bool isDeadBool;
	bool isOnGround;
	float speed;
	float hp;
	float delayTime;
	sf::Vector2f velocity;

};

