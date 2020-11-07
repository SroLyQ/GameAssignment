#include "Player.h"
#include "Animation.h"
#include "bullet.h"
#include "Initial.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight):
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->gunType = 0;
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
	gunTextureRec.setPosition(body.getPosition().x + 15.0f, body.getPosition().y);
	setGunTexture(&gunTexture);
}
Player::~Player()
{
}
void Player::Update(sf::Texture* texture, float deltaTime)
{
	shootingBool = false;
	velocity.x = 0.0f;
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
	if (faceRight) {
		switch (this->gunType) {
			case 0:
				gunTexture.loadFromFile("./Sprite/Object/Guns/0_R.png");
				gunTextureRec.setSize(sf::Vector2f(20.0f, 10.0f));
				gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
				gunTextureRec.setTexture(&gunTexture);
				break;
			case 1:
				gunTexture.loadFromFile("./Sprite/Object/Guns/1.png");
				gunTextureRec.setSize(sf::Vector2f(30.0f, 16.0f));
				gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
				gunTextureRec.setTexture(&gunTexture);
				break;
			case 2:
				gunTexture.loadFromFile("./Sprite/Object/Guns/2.png");
				gunTextureRec.setSize(sf::Vector2f(24.0f, 12.0f));
				gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
				gunTextureRec.setTexture(&gunTexture);
				break;
		}
		gunTextureRec.setPosition(body.getPosition().x + 15.0f, body.getPosition().y+5.0f);
	}
	else if (!faceRight) {
		switch (this->gunType) {
		case 0:
			gunTexture.loadFromFile("./Sprite/Object/Guns/0_L.png");
			gunTextureRec.setSize(sf::Vector2f(20.0f, 10.0f));
			gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
			gunTextureRec.setTexture(&gunTexture);
			break;
		case 1:
			gunTexture.loadFromFile("./Sprite/Object/Guns/1.png");
			gunTextureRec.setSize(sf::Vector2f(24.0f, 16.0f));
			gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
			gunTextureRec.setTexture(&gunTexture);
			break;
		case 2:
			gunTexture.loadFromFile("./Sprite/Object/Guns/2.png");
			gunTextureRec.setSize(sf::Vector2f(24.0f, 12.0f));
			gunTextureRec.setOrigin(gunTextureRec.getSize() / 2.0f);
			gunTextureRec.setTexture(&gunTexture);
			break;
		}
		gunTextureRec.setPosition(body.getPosition().x - 15.0f, body.getPosition().y+5.0f);
	}
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
