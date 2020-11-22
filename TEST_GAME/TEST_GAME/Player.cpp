#include "Player.h"
#include "Animation.h"
#include "bullet.h"
#include "Initial.h"
#include <math.h>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->hp = 6;
	this->jumpHeight = jumpHeight;
	this->gunType = 0;
	this->gunType1ClockFloat = 0.0f;
	this->gunType2ClockFloat = 0.0f;
	this->gunType3ClockFloat = 0.0f;
	this->restartClock = false;
	this->isImmuneBool = false;
	this->faceRight = true;
	this->canJump = true;
	this->shootingBool = false;

	iconTexture.loadFromFile("./Sprite/Player/icon.png");
	fullHeartTexture.loadFromFile("./Sprite/Player/FullHeart.png");
	halfHeartTexture.loadFromFile("./Sprite/Player/HalfHeart.png");
	emptyHeartTexture.loadFromFile("./Sprite/Player/EmptyHeart.png");
	gunTexture.loadFromFile("./Sprite/Object/Guns/0_R.png");

	body.setSize(sf::Vector2f(30.0f, 37.0f));
	body.setPosition(540.0f, 50.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setFillColor(sf::Color(255, 255, 255, 0));

	bodyTexture.setSize(sf::Vector2f(35.0f, 42.0f));
	bodyTexture.setPosition(540.0f, 50.0f);
	bodyTexture.setOrigin(bodyTexture.getSize() / 2.0f);
	bodyTexture.setTexture(texture);

	icon.setSize(sf::Vector2f(35.0f, 35.0f));
	icon.setOrigin(icon.getSize() / 2.0f);
	icon.setPosition(48.0f, 40.0f);
	icon.setTexture(&iconTexture);

	heart[0].setSize(sf::Vector2f(35.0f, 35.0f));
	heart[0].setOrigin(heart[0].getSize() / 2.0f);
	heart[0].setPosition(183.0f, 40.0f);
	heart[0].setTexture(&fullHeartTexture);

	heart[1].setSize(sf::Vector2f(35.0f, 35.0f));
	heart[1].setOrigin(heart[1].getSize() / 2.0f);
	heart[1].setPosition(138.0f, 40.0f);
	heart[1].setTexture(&fullHeartTexture);

	heart[2].setSize(sf::Vector2f(35.0f, 35.0f));
	heart[2].setOrigin(heart[2].getSize() / 2.0f);
	heart[2].setPosition(93.0f,40.0f);
	heart[2].setTexture(&fullHeartTexture);

	gunTextureRec.setSize(sf::Vector2f(20.0f, 10.0f));
	gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
	gunTextureRec.setPosition(body.getPosition().x + 20.0f, body.getPosition().y);
	setGunTexture(&gunTexture);
}
Player::~Player()
{
}
void Player::Update(sf::Texture* texture, float deltaTime, std::vector<sf::Texture*> gunTexture_R)
{
	shootingBool = false;
	velocity.x = 0.0f;
	if (isImmuneBool) {
		immuneClockFloat = immuneClock.getElapsedTime().asSeconds();
		if (immuneClockFloat > 2.2f) {
			isImmuneBool = false;
			immuneClock.restart();
			immuneClockFloat = 0.0f;
		}
		else if (immuneClockFloat < 0.5f) {
			bodyTexture.setFillColor(sf::Color(255, 255, 255, 100));
			isImmuneBool = true;
		}
		else if (immuneClockFloat < 1.0f) {
			bodyTexture.setFillColor(sf::Color(255, 255, 255, 255));
			isImmuneBool = true;
		}
		else if (immuneClockFloat < 1.5f) {
			bodyTexture.setFillColor(sf::Color(255, 255, 255, 100));
			isImmuneBool = true;
		}
		else if (immuneClockFloat < 2.0f) {
			bodyTexture.setFillColor(sf::Color(255, 255, 255, 255));
			isImmuneBool = true;
		}
	}
	else {
		immuneClock.restart();
		immuneClockFloat = 0.0f;
	}
	switch (this->hp) {
		case 6:
			heart[0].setTexture(&fullHeartTexture);
			heart[1].setTexture(&fullHeartTexture);
			heart[2].setTexture(&fullHeartTexture);
			break;
		case 5:
			heart[0].setTexture(&halfHeartTexture);
			heart[1].setTexture(&fullHeartTexture);
			heart[2].setTexture(&fullHeartTexture);
			break;
		case 4:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&fullHeartTexture);
			heart[2].setTexture(&fullHeartTexture);
			break;
		case 3:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&halfHeartTexture);
			heart[2].setTexture(&fullHeartTexture);
			break;
		case 2:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&emptyHeartTexture);
			heart[2].setTexture(&fullHeartTexture);
			break;
		case 1:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&emptyHeartTexture);
			heart[2].setTexture(&halfHeartTexture);
			break;
		case 0:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&emptyHeartTexture);
			heart[2].setTexture(&emptyHeartTexture);
			break;
		case -1:
			heart[0].setTexture(&emptyHeartTexture);
			heart[1].setTexture(&emptyHeartTexture);
			heart[2].setTexture(&emptyHeartTexture);
			break;
	}
	switch (this->gunType) {
	case 0:
		delayShoot = 500.0f;
		gunTextureRec.setSize(sf::Vector2f(20.0f, 10.0f));
		gunType1Clock.restart();
		gunType2Clock.restart();
		gunType3Clock.restart();
		break;
	case 1:
		delayShoot = 100.0f;
		gunTextureRec.setSize(sf::Vector2f(30.0f, 16.0f));
		gunType1ClockFloat = gunType1Clock.getElapsedTime().asSeconds();
		gunType2Clock.restart();
		gunType3Clock.restart();
		break;
	case 2:
		delayShoot = 700.0f;
		gunTextureRec.setSize(sf::Vector2f(24.0f, 12.0f));
		gunType2ClockFloat = gunType2Clock.getElapsedTime().asSeconds();
		gunType1Clock.restart();
		gunType3Clock.restart();
		break;
	case 3:
		delayShoot = 950.0f;
		gunTextureRec.setSize(sf::Vector2f(34.0f, 16.0f));
		gunType3ClockFloat = gunType3Clock.getElapsedTime().asSeconds();
		gunType1Clock.restart();
		gunType2Clock.restart();
	}
	if (restartClock) {
		gunType1Clock.restart();
		gunType2Clock.restart();
		gunType3Clock.restart();
		restartClock = false;
	}
	if (gunType1ClockFloat > 8.0f) {
		this->gunType = 0;
		gunType1Clock.restart();
		gunType1ClockFloat = 0.0f;
	}
	else if (gunType2ClockFloat > 9.0f) {
		this->gunType = 0;
		gunType2Clock.restart();
		gunType2ClockFloat = 0.0f;
	}
	else if (gunType3ClockFloat > 7.0f) {
		this->gunType = 0;
		gunType3Clock.restart();
		gunType3ClockFloat = 0.0f;
	}
	gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
	if (faceRight) {
		this->gunTextureRec.setTexture(gunTexture_R[this->gunType]);
		this->gunTextureRec.setTextureRect(sf::IntRect(0, 0, abs(gunTexture_R[this->gunType]->getSize().x / 1.0f), gunTexture_R[this->gunType]->getSize().y));
		gunTextureRec.setPosition(body.getPosition().x + 20.0f, body.getPosition().y);
	}
	else if (!faceRight) {
		this->gunTextureRec.setTexture(gunTexture_R[this->gunType]);
		this->gunTextureRec.setTextureRect(sf::IntRect(gunTexture_R[this->gunType]->getSize().x, 0, -abs(gunTexture_R[this->gunType]->getSize().x / 1.0f), gunTexture_R[this->gunType]->getSize().y));
		gunTextureRec.setPosition(body.getPosition().x - 20.0f, body.getPosition().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = 981.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (shootingBool == false)
			shootingBool = true;
	}
	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f) {
		texture->loadFromFile("Sprite/Player/Animation_Idle_R.png");
	}
	else {
		texture->loadFromFile("Sprite/Player/Animation_Walk_R.png");
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	animation.Update(deltaTime, faceRight);
	bodyTexture.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	bodyTexture.setPosition(body.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(heart[0]);
	window.draw(heart[1]);
	window.draw(heart[2]);
	window.draw(icon);
	window.draw(gunTextureRec);
	window.draw(bodyTexture);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
	}
}

void Player::setGunType(int gunType)
{
	if (this->gunType != gunType) {
		this->gunType = gunType;
	}
	else this->restartClock = true;
}

void Player::setGunTexture(sf::Texture* texture)
{
	gunTextureRec.setTexture(texture);
}

void Player::changeHp(int hpChanger)
{
	this->hp += hpChanger;
}

void Player::setIsImmune(bool isImmune)
{
	this->isImmuneBool = isImmune;
}
