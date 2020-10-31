#include "Player.h"
#include "Animation.h"
#include "bullet.h"
#include "Initial.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight):
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	faceRight = true;
	canJump = true;
	shootingBool = false;

	body.setSize(sf::Vector2f(35.0f,42.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(540.0f, 50.0f);
	body.setTexture(texture);
}
Player::~Player()
{
}
void Player::Update(sf::Texture* texture,float deltaTime)
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
		if(shootingBool==false)
			shootingBool = true;
	}
	//std::cout << velocity.x << " " << velocity.y << std::endl;
	velocity.y += 981.0f*deltaTime;

	if (velocity.x == 0.0f){
		texture->loadFromFile("Sprite/Player/Animation_Idle_R.png");
	}
	else {
		texture->loadFromFile("Sprite/Player/Animation_Walk_R.png");
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	switch (gunType){
		case 1:
			delayShoot = 500.0f;
			break;
	}
	animation.Update(deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity*deltaTime);

}

void Player::Draw(sf::RenderWindow& window)
{
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
