#pragma once
#include "Initial.h"
#include "Collider.h"
class Gun
{
public:
	Gun(int type,Collider col,std::vector<sf::Texture*> vectTexture);

	void Draw(sf::RenderWindow& window);
	void setPickUp(bool isPickUp);

	bool isPickUp() { return isPickUpBool; }
	int GetGunType() { return type; }
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Texture* texture;

	bool isPickUpBool;
	int type;
};

