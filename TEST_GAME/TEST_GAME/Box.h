#pragma once
#include "Initial.h"
#include "Collider.h"
class Box
{
public:
	Box(sf::Texture* texture,sf::Vector2f position);
	~Box();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);

	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }

private:
	sf::RectangleShape body;

	sf::Vector2f velocity;
	int type;
};

