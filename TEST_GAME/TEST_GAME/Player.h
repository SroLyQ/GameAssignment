#pragma once
#include "Initial.h"
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime,float speed,float jumpHeight);
	~Player();

	void Update(sf::Texture* texture,float deltaTime, std::vector<sf::Texture*> gunTexture_R ,State* state);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void setGunType(int gunType);
	void setGunTexture(sf::Texture* texture);
	void changeHp(int hpChanger);
	void setIsImmune(bool isImmune);
	void setPauseTime(float pauseTime);
	void restart();

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetGunPosition() { return gunTextureRec.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	float getShootDelayTime() { return delayShoot; }
	bool isFaceRight() { return faceRight; }
	bool isShooting() { return shootingBool; }
	bool isImmune() { return isImmuneBool; }
	bool isDead() { return isDeadBool; }
	int getHp() { return hp; }
	int GetGunType() { return gunType; }

private:
	sf::RectangleShape body;
	sf::RectangleShape bodyTexture;
	sf::RectangleShape gunTextureRec;
	sf::RectangleShape icon;
	sf::RectangleShape heart[4];
	sf::Texture gunTexture;
	sf::Texture fullHeartTexture;
	sf::Texture halfHeartTexture;
	sf::Texture emptyHeartTexture;
	sf::Texture iconTexture;
	sf::Vector2f velocity;
	sf::Clock gunType1Clock;
	sf::Clock gunType2Clock;
	sf::Clock gunType3Clock;
	sf::Clock immuneClock;
	Animation animation;

	float gunType1ClockFloat;
	float gunType2ClockFloat;
	float gunType3ClockFloat;
	float speed;
	float jumpHeight;
	float delayShoot;
	float immuneClockFloat;
	float pauseTimeGun;
	float pauseTimeImmune;
	bool restartClock;
	bool  faceRight;
	bool shootingBool;
	bool canJump;
	bool isImmuneBool;
	bool isDeadBool;
	int hp;
	int gunType;

};

