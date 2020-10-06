#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collider.h"
#include "Platform.h"
int main()
{
	/// Window ///
	sf::RenderWindow window(sf::VideoMode(1080, 720), "TEST_GAME", sf::Style::Close | sf::Style::Resize);
	//variable
	bool isMoving = false, isLeft = false, isRight = true;
	// Platform //
	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));
	/// Texture ///
	sf::Texture playerTexture;
	sf::Texture BG_ColorTexture;
	sf::Texture BG_BuildingTexture;

	playerTexture.loadFromFile("Sprite/Player/Animation_Idle_R.png");
	BG_ColorTexture.loadFromFile("Sprite/Background/BG_Color.png");
	BG_BuildingTexture.loadFromFile("Sprite/Background/Buildings.png");
	/// Sprite ///
	sf::Sprite player;
	sf::Sprite BG_Color;
	sf::Sprite BG_Building;

	BG_Building.setTexture(BG_BuildingTexture);
	BG_Color.setTexture(BG_ColorTexture);
	player.setTexture(playerTexture);
	player.setPosition(538.0f,360.0f);
	player.setScale(3, 3);

	int spriteSizeX = playerTexture.getSize().x / 5;
	int bgStartX = 0;
	player.setTextureRect(sf::IntRect(0, 0, spriteSizeX, 12));


	// ANIMATION //
	float switchTime = 0.15f,totalTime=0.0f,deltaTime=0.0f;
	int PlayerAnimationFrame = 0;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		sf::Event evnt;
		window.draw(BG_Color);
		window.draw(BG_Building);
		//Event
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:

					break;
			}
		}
		//Platform//
		//platform1.GetCollider().CheckCollision(player.GetCollider(),0.0f);
		//platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
			platform1.Draw(window);
			platform2.Draw(window);
		//PlatformEnd//
		//EventEnd
		//Move
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			isMoving = true;
			isLeft = false;
			isRight = true;
			playerTexture.loadFromFile("Sprite/Player/Animation_Walk_R.png");
			player.move(.2f, 0.f);
			player.setTextureRect(sf::IntRect(spriteSizeX * PlayerAnimationFrame,1,spriteSizeX, 12));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			isMoving = true;
			isLeft = true;
			isRight = false;
			playerTexture.loadFromFile("Sprite/Player/Animation_Walk_L.png");
			player.move(-.2f, 0.f);
			player.setTextureRect(sf::IntRect(spriteSizeX * PlayerAnimationFrame, 1, spriteSizeX, 12));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		isMoving = false;
		//MoveEnd
		//Animation
		deltaTime = clock.restart().asSeconds();
		window.draw(player);
		window.display();
		if (!isMoving && isRight) {
			playerTexture.loadFromFile("Sprite/Player/Animation_Idle_R.png");
			player.setTextureRect(sf::IntRect(spriteSizeX * PlayerAnimationFrame, 1, spriteSizeX, 12));
		}
		if (!isMoving && isLeft) {
			playerTexture.loadFromFile("Sprite/Player/Animation_Idle_L.png");
			player.setTextureRect(sf::IntRect(spriteSizeX * PlayerAnimationFrame, 1, spriteSizeX, 12));
		}
		totalTime +=  deltaTime;
		if (totalTime >= switchTime) {
			totalTime -= switchTime;
			PlayerAnimationFrame++;
			if (PlayerAnimationFrame >= 4) {
				PlayerAnimationFrame = 0;
			}
			
		}
		//AnimationEnd
		window.clear(sf::Color(155,155,155));
	}
	return 0;
}