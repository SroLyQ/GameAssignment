#include "Player.h"
#include "Animation.h"
#include "bullet.h"
#include "Initial.h"
#include <math.h>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight):
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->gunType = 0;
	this->gunType1ClockFloat = 0.0f;
	this->gunType2ClockFloat = 0.0f;
	gunTexture.loadFromFile("./Sprite/Object/Guns/0_R.png");
	faceRight = true;
	canJump = true;
	shootingBool = false;
	body.setSize(sf::Vector2f(35.0f,42.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(540.0f, 50.0f);
	body.setTexture(texture);
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
	switch (this->gunType) {
		case 0:
			gunTextureRec.setSize(sf::Vector2f(20.0f, 10.0f));
			gunType1Clock.restart();
			gunType2Clock.restart();
			break;
		case 1:
			gunTextureRec.setSize(sf::Vector2f(30.0f, 16.0f));
			gunType1ClockFloat = gunType1Clock.getElapsedTime().asSeconds();
			gunType2Clock.restart();
			break;
		case 2:
			gunTextureRec.setSize(sf::Vector2f(24.0f, 12.0f));
			gunType2ClockFloat = gunType2Clock.getElapsedTime().asSeconds();
			gunType1Clock.restart();
			break;
	}
	if (gunType1ClockFloat > 10.0f) {
		this->gunType = 0;
		gunType1Clock.restart();
		gunType1ClockFloat = 0.0f;
	}
	else if (gunType2ClockFloat > 15.0f) {
		this->gunType = 0;
		gunType2Clock.restart();
		gunType2ClockFloat = 0.0f;
	}
	gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
	if (faceRight) {
		this->gunTextureRec.setTexture(gunTexture_R[this->gunType]);
		this->gunTextureRec.setTextureRect(sf::IntRect(0, 0, abs(gunTexture_R[this->gunType]->getSize().x/1.0f), gunTexture_R[this->gunType]->getSize().y));
		gunTextureRec.setPosition(body.getPosition().x + 20.0f, body.getPosition().y);
	}
	else if (!faceRight) {
		this->gunTextureRec.setTexture(gunTexture_R[this->gunType]);
		this->gunTextureRec.setTextureRect(sf::IntRect(gunTexture_R[this->gunType]->getSize().x , 0, -abs(gunTexture_R[this->gunType]->getSize().x / 1.0f), gunTexture_R[this->gunType]->getSize().y));
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
	//std::cout << velocity.x << " " << velocity.y << std::endl;
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
	switch (this->gunType) {
	case 0:
		delayShoot = 500.0f;
		break;
	case 1:
		delayShoot = 100.0f;
		break;
	case 2:
		delayShoot = 1000.0f;
		break;
	}
	animation.Update(deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(gunTextureRec);
	window.draw(body);
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
	this->gunType = gunType;
}

void Player::setGunTexture(sf::Texture* texture)
{
		gunTextureRec.setTexture(texture);
}
