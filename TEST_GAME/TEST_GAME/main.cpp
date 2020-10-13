#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collider.h"
#include "Platform.h"
#include "Player.h"
#include <vector>

void collisionWith(std::vector<Platform>& vect, Player& player, Collider col, sf::Vector2f direction);
void drawPlatform(std::vector<Platform>& vect, sf::RenderWindow& window);
int main()
{
	std::vector<Platform> platforms;
	std::vector<Platform> walls;
	std::vector<Platform> spawns;
	/// Texture ///
	sf::Texture playerTexture;
	sf::Texture BG_ColorTexture;
	sf::Texture BG_BuildingTexture;
	sf::Texture Wall1;
	sf::Texture Floor1;
	sf::Texture Platform1;
	/// Window ///
	sf::RenderWindow window(sf::VideoMode(1080, 720), "TEST_GAME", sf::Style::Close | sf::Style::Resize);
	//variable
	bool isMoving = false, isLeft = false, isRight = true;
	// Platform //
	Wall1.loadFromFile("Sprite/Map/Wall1.png");
	Floor1.loadFromFile("Sprite/Map/Floor1.png");
	Platform1.loadFromFile("Sprite/Map/Platform1.png");
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(12.5f, 120.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(12.5f, 360.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(12.5f, 600.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(1067.5f, 120.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(1067.5f, 360.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(30.0f, 240.0f), sf::Vector2f(1067.5f, 600.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(500.0f, 40.0f), sf::Vector2f(250.0f, 0.0f)));
	walls.push_back(Platform(&Wall1, sf::Vector2f(500.0f, 40.0f), sf::Vector2f(830.0f, 0.0f)));
	walls.push_back(Platform(&Floor1, sf::Vector2f(472.0f, 80.0f), sf::Vector2f(263.5f, 720.0f)));
	walls.push_back(Platform(&Floor1, sf::Vector2f(472.0f, 80.0f), sf::Vector2f(816.0f, 720.0f)));

	platforms.push_back(Platform(&Platform1, sf::Vector2f(300.0f, 25.0f), sf::Vector2f(540.0f, 120.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(300.0f, 25.0f), sf::Vector2f(540.0f, 360.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(300.0f, 25.0f), sf::Vector2f(540.0f, 600.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(400.0f, 25.0f), sf::Vector2f(228.0f, 240.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(400.0f, 25.0f), sf::Vector2f(228.0f, 480.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(400.0f, 25.0f), sf::Vector2f(852.0f, 240.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(400.0f, 25.0f), sf::Vector2f(852.0f, 480.0f)));


	spawns.push_back(Platform(nullptr, sf::Vector2f(80.0f, 40.0f), sf::Vector2f(540.0f, 5.0f)));
	spawns.push_back(Platform(nullptr, sf::Vector2f(80.0f, 40.0f), sf::Vector2f(540.0f, 715.0f)));

	if (!playerTexture.loadFromFile("Sprite/Player/Animation_Idle_R.png")) printf("Load File Error");
	BG_ColorTexture.loadFromFile("Sprite/Background/BG_Color.png");
	BG_BuildingTexture.loadFromFile("Sprite/Background/Buildings.png");

	/// Sprite ///
	sf::Sprite BG_Color;
	sf::Sprite BG_Building;

	BG_Building.setTexture(BG_BuildingTexture);
	BG_Color.setTexture(BG_ColorTexture);


	// ANIMATION //
	Player player(&playerTexture, sf::Vector2u(5, 1), 0.135f,200.0f,140.0f);
	float deltaTime = 0.0f;
	sf::Clock clock;
	
	//Collider
	Collider col = player.GetCollider();
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 200.0f) {
			deltaTime = 1.0f / 200.0f;
		}
		sf::Event evnt;
		window.draw(BG_Color);
		window.draw(BG_Building);
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:

				break;
			}
		}
		player.Update(&playerTexture,deltaTime);	
		 
		sf::Vector2f direction;

		collisionWith(walls, player, col, direction);
		collisionWith(platforms, player, col, direction);
		collisionWith(spawns, player, col, direction);
		drawPlatform(walls, window);
		drawPlatform(platforms, window);
		drawPlatform(spawns, window);
		player.Draw(window);
		window.display();
	}
	return 0;
}
void collisionWith(std::vector<Platform> &vect,Player  &player,Collider col,sf::Vector2f direction) {
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			player.OnCollision(direction);
		}
	}
}
void drawPlatform(std::vector<Platform>& vect,sf::RenderWindow &window) {
	for (Platform& platform : vect)
	{
		platform.Draw(window);
	}
}