#pragma once
#include "Initial.h"
#include "Collider.h"
#include "Bullet.h"
#include "Gun.h"

class Box
{
public:
	Box(sf::Texture* texture,sf::Vector2f position,int gunType);
	~Box();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);
	void hitWithBullet(Bullet& bullet);

	int GetGunType() { return gunType; }
	bool isDesttoy() { return isDestroyBool; }
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }

private:
	sf::RectangleShape body;

	bool isDestroyBool;
	sf::Vector2f velocity;
	float hp;
	int gunType;
};

