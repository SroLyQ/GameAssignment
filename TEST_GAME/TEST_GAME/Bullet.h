#pragma once
#include "Initial.h"
#include "Collider.h"
#include "Player.h"
class Bullet
{
public:
	Bullet(sf::Texture*texture,int type, bool faceRight, sf::Vector2f position);
	~Bullet();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void setDestroy(bool isDestroy);
	
	float getTimeAlive() { return fadingTime; }
	int GetType() { return type; }
	Collider GetCollider() { return Collider(body); }
	bool isDestroy() { return isDestroyBool; }
	float GetDamage() { return damage; }

private:
	sf::RectangleShape body;
	sf::RectangleShape textureRec;
	sf::Clock fadingClock;
	sf::Vector2f velocity;
	
	float fadingTime;
	bool faceRight;
	float speed;
	int type;
	bool isDestroyBool;
	bool isFadingBool;
	float damage;
};

