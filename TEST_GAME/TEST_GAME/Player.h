#pragma once
#include "Initial.h"
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime,float speed,float jumpHeight);
	~Player();

	void Update(sf::Texture* texture,float deltaTime, std::vector<sf::Texture*> gunTexture_R );
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void setGunType(int gunType);
	void setGunTexture(sf::Texture* texture);

	int GetGunType() { return gunType; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetGunPosition() { return gunTextureRec.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isFaceRight() { return faceRight; }
	bool isShooting() { return shootingBool; }
	float getShootDelayTime() { return delayShoot; }
	float getHp() { return hp; }

private:
	sf::RectangleShape body;
	sf::RectangleShape gunTextureRec;
	sf::Texture gunTexture;
	sf::Vector2f velocity;
	Animation animation;
	sf::Clock gunType1Clock;
	sf::Clock gunType2Clock;
	sf::Clock gunType3Clock;

	float gunType1ClockFloat;
	float gunType2ClockFloat;
	float gunType3ClockFloat;
	float speed;
	bool restartClock;
	bool  faceRight;
	bool shootingBool;
	float hp;
	bool canJump;
	float jumpHeight;
	float delayShoot;
	int gunType;

};

