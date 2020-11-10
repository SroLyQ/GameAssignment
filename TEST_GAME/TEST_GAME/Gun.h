#pragma once
#include "Initial.h"
#include "Collider.h"
class Gun
{
public:
	Gun(int type,Collider col,std::vector<sf::Texture*> vectTexture);

	void Draw(sf::RenderWindow& window);
	void setPickUp(bool isPickUp);
	void Update(float deltaTime);

	bool isDestroy() { return isDestroyBool; }
	bool isPickUp() { return isPickUpBool; }
	int GetGunType() { return type; }
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Texture* texture;
	sf::Clock clockAlive;
	sf::Vector2f startPosition;

	float timeAlive;
	float speed;
	bool moveUp;
	bool isPickUpBool;
	bool isDestroyBool;
	int type;
};

