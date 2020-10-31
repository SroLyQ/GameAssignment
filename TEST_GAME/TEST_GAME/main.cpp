#include "Initial.h"
#include "Collider.h"
#include "Platform.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include "Box.h"

void bulletCollisionWithEnemies(std::vector<Bullet>& vect, Enemy& enemy, Collider col, sf::Vector2f direction);
void platformCollisionWithBullets(std::vector<Platform>& vect, Bullet& bullet, Collider col, sf::Vector2f direction);
void playerCollisionWithPlatforms(std::vector<Platform>& vect, Player& player, Collider col, sf::Vector2f direction);
void enemyCollisionWithPlatforms(std::vector<Platform>& vect, Enemy& enemy, Collider col, sf::Vector2f direction);
void drawPlatform(std::vector<Platform>& vect, sf::RenderWindow& window);
void drawBullet(std::vector<Bullet>& vect, sf::RenderWindow& window);
void drawEnemies(std::vector<Enemy>& vect, sf::RenderWindow& window);
void updateBullet(std::vector<Bullet>& vect, float deltaTime);
void updateEnemies(std::vector<Enemy>& vect, float deltaTime, std::vector<Box>& vectBox, sf::Texture* texture);
void createEnemy(std::vector<Enemy>& vect, int type, sf::Texture* textureG, sf::Texture* textureR);
void drawBoxes(std::vector<Box>& vect, sf::RenderWindow& window);
void updateBoxes(std::vector<Box>& vect, float deltaTime);

int main()
{
	std::vector<Box> boxes;
	std::vector<Platform> platforms;
	std::vector<Platform> walls;
	std::vector<Platform> spawns;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	/// Texture ///
	sf::Texture playerTexture;
	sf::Texture BG_ColorTexture;
	sf::Texture BG_BuildingTexture;
	sf::Texture Wall1;
	sf::Texture Floor1;
	sf::Texture Platform1;
	sf::Texture spawnTop;
	sf::Texture enemyTextureG;
	sf::Texture enemyTextureR;
	sf::Texture boxTexture;


	if (!boxTexture.loadFromFile("Sprite/Object/Crate.png")) printf("Load File Error");
	if (!playerTexture.loadFromFile("Sprite/Player/Animation_Idle_R.png")) printf("Load File Error");
	BG_ColorTexture.loadFromFile("Sprite/Background/BG_Color.png");
	BG_BuildingTexture.loadFromFile("Sprite/Background/Buildings.png");
	if (!enemyTextureG.loadFromFile("Sprite/Monster/Animation_Walk_Monster1.png")) printf("Load File Error");
	if (!enemyTextureR.loadFromFile("Sprite/Monster/Animation_Walk_Monster1.png")) printf("Load File Error");

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
	Collider playerCol = player.GetCollider();


	//Clock
	sf::Clock delayShootClock;
	sf::Clock delayEnemySpawnClock;
	
	//Timer
	float delayShoot;
	float delayEnemySpawn;

	//rand
	srand(time(NULL));

	//temp
	float enemyRespawnTimeClamp=1500.0f;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		delayShoot = delayShootClock.getElapsedTime().asMilliseconds();
		delayEnemySpawn = delayEnemySpawnClock.getElapsedTime().asMilliseconds();
		if (deltaTime > 1.0f / 400.0f) {
			deltaTime = 1.0f / 400.0f;
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
		sf::Vector2f direction;
		player.Update(&playerTexture,deltaTime);	
		player.setGunType(1);
		if (delayEnemySpawn > std::fmax(500.0f,std::fmax((std::fmod(rand(),enemyRespawnTimeClamp+1)),enemyRespawnTimeClamp))) {
			int temprand = rand() % 2;
			createEnemy(enemies, temprand, &enemyTextureG, &enemyTextureR);
			delayEnemySpawnClock.restart();
			if (enemyRespawnTimeClamp > 1000.0f) {
				enemyRespawnTimeClamp-=5;
			}
		}
		updateEnemies(enemies, deltaTime, boxes, &boxTexture);
		updateBullet(bullets, deltaTime); 
		for (int i = 0;i < enemies.size();i++) {

				Collider temp = enemies[i].GetCollider();
				enemyCollisionWithPlatforms(walls, enemies[i], temp, direction);
				enemyCollisionWithPlatforms(platforms, enemies[i], temp, direction);
				bulletCollisionWithEnemies(bullets, enemies[i], temp, direction);
		}
		if (player.isShooting() && delayShoot > player.getShootDelayTime()) {
			bullets.push_back(Bullet(nullptr, 1, player.isFaceRight(),player.GetPosition()));
			delayShootClock.restart();
		}   
		for (int i = 0;i < bullets.size();i++) {
			Collider temp = bullets[i].GetCollider();
			platformCollisionWithBullets(walls, bullets[i], temp, direction);
			platformCollisionWithBullets(platforms, bullets[i], temp, direction);
		}

		playerCollisionWithPlatforms(walls, player, playerCol, direction);
		playerCollisionWithPlatforms(platforms, player, playerCol, direction);
		playerCollisionWithPlatforms(spawns, player, playerCol, direction);
		drawPlatform(walls, window);
		drawPlatform(platforms, window);
		drawBullet(bullets, window);
		drawBoxes(boxes, window);
		drawEnemies(enemies, window);
		spawns[1].Draw(window);
		player.Draw(window);
		window.display();
	}
	return 0;
}
void playerCollisionWithPlatforms(std::vector<Platform>& vect, Player& player, Collider col, sf::Vector2f direction) {
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			player.OnCollision(direction);
		}
	}
}
void enemyCollisionWithPlatforms(std::vector<Platform>& vect, Enemy& enemy, Collider col, sf::Vector2f direction) {
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			enemy.OnCollision(direction);
		}
	}
}
void platformCollisionWithBullets(std::vector<Platform>& vect, Bullet& bullet, Collider col, sf::Vector2f direction) {
	for (Platform& platform : vect) {
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			bullet.setDestroy(true);
			//std::cout << bullet.isDestroy() << std::endl;
		}
	}
}
void bulletCollisionWithEnemies(std::vector<Bullet>& vect, Enemy& enemy, Collider col, sf::Vector2f direction) {
	for (Bullet& bullet : vect) {
		if (bullet.GetCollider().CheckCollision(col, direction, 1.0f)) {
			bullet.setDestroy(true);
			enemy.hitWithBullet(bullet);
		}
	}
}
void drawPlatform(std::vector<Platform>& vect,sf::RenderWindow &window) {
	for (Platform& platform : vect)
	{
		platform.Draw(window);
	}
}
void drawBullet(std::vector<Bullet>& vect, sf::RenderWindow& window) {
	for (Bullet& bullet : vect) {
		bullet.Draw(window);
	}
}
void drawEnemies(std::vector<Enemy>& vect, sf::RenderWindow& window) {
	for (Enemy& enemy : vect) {
		enemy.Draw(window);
	}
}
void drawBoxes(std::vector<Box>& vect, sf::RenderWindow& window) {
	for (Box& box : vect) {
		box.Draw(window);
	}
}
void updateBullet(std::vector<Bullet>& vect, float deltaTime) {
	for (Bullet& bullet : vect) {
		bullet.Update(deltaTime);
	}
	for (int i = 0;i < vect.size();i++) {
		if (vect[i].isDestroy()) {
			vect.erase(vect.begin() + i);
		}
	}
}
void updateEnemies(std::vector<Enemy>& vect, float deltaTime, std::vector<Box> & vectBox,sf::Texture* texture) {
	for (Enemy& enemy : vect) {
		enemy.Update(deltaTime);
	}
	for (int i = 0;i < vect.size();i++) {
		if (vect[i].getHp()<=0) {
			vect[i].spawnBox();
			std::cout << vect[i].isSpawnBox() << std::endl;
			if (vect[i].isSpawnBox()) {
				vectBox.push_back(Box(texture , vect[i].GetPosition()));
			}
			vect.erase(vect.begin() + i);
		}
	}
}
void updateBoxes(std::vector<Box>& vect, float deltaTime) {
	for (Box& box : vect) {
		box.Update(deltaTime);
	}
}
void createEnemy(std::vector<Enemy>& vect, int type,sf::Texture *textureG,sf::Texture *textureR) {
	switch (type) {
		case 0:
			vect.push_back(Enemy(textureG, sf::Vector2u(11, 1), 0.095f, 150.0f, 1));
			break;
		case 1:
			vect.push_back(Enemy(textureR, sf::Vector2u(11, 1), 0.095f, 150.0f, 1));
			break;
	}
}
void boxCollisionWithPlatforms(std::vector<Platform>& vect, Box& box, Collider col, sf::Vector2f direction) {
	for (Platform& platform : vect) {
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			box.OnCollision(direction);
		}
	}
}