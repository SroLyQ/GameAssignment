#define _CRT_SECURE_NO_WARNINGS
#include "Initial.h"
#include "Collider.h"
#include "Platform.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Box.h"
#include "Gun.h"
#include "Button.h"
#include "Textbox.h"
#include <utility>
#include <algorithm>
#include <string>

void showText(sf::Vector2f position, std::string word, sf::Font* font, int size, sf::RenderWindow& window);
void playerCollisionWithEnemy(std::vector<Enemy>& vect, Player& player, Collider playerCol, sf::Vector2f direction);
void playerCollisionWithGuns(std::vector<Gun>& vect, Player& player, Collider col, sf::Vector2f direction);
void boxCollisionWithPlatforms(std::vector<Platform>& vect, Box& box, Collider col, sf::Vector2f direction);
void bulletCollisionWithEnemies(std::vector<Bullet>& vect, Enemy& enemy, Collider col, sf::Vector2f direction, sf::Sound* sound);
void platformCollisionWithBullets(std::vector<Platform>& vect, Bullet& bullet, Collider col, sf::Vector2f direction);
void playerCollisionWithPlatforms(std::vector<Platform>& vect, Player& player, Collider col, sf::Vector2f direction);
void enemyCollisionWithPlatforms(std::vector<Platform>& vect, Enemy& enemy, Collider col, sf::Vector2f direction);
void bulletCollisionWithBoxes(std::vector<Bullet>& vect, Box& box, Collider col, sf::Vector2f direction, sf::Sound* sound);
void drawPlatform(std::vector<Platform>& vect, sf::RenderWindow& window);
void drawBullet(std::vector<Bullet>& vect, sf::RenderWindow& window);
void drawEnemies(std::vector<Enemy>& vect, sf::RenderWindow& window);
void updateBullet(std::vector<Bullet>& vect, float deltaTime);
void updateEnemies(std::vector<Enemy>& vect, float deltaTime, std::vector<Box>& vectBox, sf::Texture* texture, int& score);
void createEnemy(std::vector<Enemy>& vect, int type, std::vector<sf::Texture*> texture, float gameTime);
void drawBoxes(std::vector<Box>& vect, sf::RenderWindow& window);
void updateBoxes(std::vector<Box>& vect, float deltaTime, std::vector<Gun>& gunVect, std::vector<sf::Texture*> gunTexture);
void drawGuns(std::vector<Gun>& vect, sf::RenderWindow& window);
void updateGuns(std::vector<Gun>& vect, float deltaTime, State& state);
void drawButtons(std::vector<Button>& vect, sf::RenderWindow& window, int gameState);
void updateButtons(std::vector<Button>& vect, sf::RenderWindow& window, int gameState, State& state);
void drawPAUSE(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font);
void drawEND_GAME(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font, int score);
void drawMENU(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font, int frame);
void eraseEnemy(std::vector<Enemy>& vect);
void eraseGun(std::vector<Gun>& vect);
void eraseBox(std::vector<Box>& vect);
void eraseBullet(std::vector<Bullet>& vect);
int main()
{
	srand(time(NULL));
	int salt1 = rand();
	srand(salt1);
	int salt2 = rand();
	srand(salt2);
	int salt3 = rand();
	srand(salt3);
	std::vector<Box> boxes;
	std::vector<Platform> platforms;
	std::vector<Platform> walls;
	std::vector<Platform> spawns;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	std::vector<Gun> guns;
	std::vector<Button> buttons;
	std::vector<sf::Texture*> gunTexture_R, enemyTexture;
	/// Texture ///
	sf::Texture playerTexture;
	sf::Texture BG_ColorTexture;
	sf::Texture BG_BuildingTexture;
	sf::Texture Wall1;
	sf::Texture Floor1;
	sf::Texture Platform1;
	sf::Texture spawnTop;
	sf::Texture enemyTexture1;
	sf::Texture enemyTexture2;
	sf::Texture boxTexture;
	sf::Texture gunTexture0;
	sf::Texture gunTexture1;
	sf::Texture gunTexture2;
	sf::Texture gunTexture3;
	sf::Texture bulletTexture;
	sf::Texture laserTexture;
	sf::Texture UIBG;
	sf::Texture HowToPlayBG;
	sf::Texture buttonBG;
	sf::Texture MENUtexture;
	sf::Texture LogoBorderTexture;
	sf::Texture deSpawn;

	MENUtexture.setRepeated(true);
	deSpawn.loadFromFile("./Sprite/Object/Spike.png");
	LogoBorderTexture.loadFromFile("./Sprite/Object/LogoFrame.png");
	gunTexture0.loadFromFile("./Sprite/Object/Guns/0_R.png");
	gunTexture1.loadFromFile("./Sprite/Object/Guns/1.png");
	gunTexture2.loadFromFile("./Sprite/Object/Guns/2.png");
	gunTexture3.loadFromFile("./Sprite/Object/Guns/3.png");
	bulletTexture.loadFromFile("./Sprite/Object/Bullet.png");
	if (!boxTexture.loadFromFile("./Sprite/Object/Crate.png")) printf("Load File Error");
	playerTexture.loadFromFile("./Sprite/Player/Animation_Idle_R.png");
	BG_ColorTexture.loadFromFile("./Sprite/Background/BG_Color.png");
	BG_BuildingTexture.loadFromFile("./Sprite/Background/Buildings.png");
	if (!enemyTexture1.loadFromFile("./Sprite/Monster/Animation_Walk_Monster1.png")) printf("Load File Error");
	if (!enemyTexture2.loadFromFile("./Sprite/Monster/Animation_Walk_Monster2.png")) printf("Load File Error");
	laserTexture.loadFromFile("./Sprite/Object/laserBullet.png");
	gunTexture_R.push_back(&gunTexture0);
	gunTexture_R.push_back(&gunTexture1);
	gunTexture_R.push_back(&gunTexture2);
	gunTexture_R.push_back(&gunTexture3);
	enemyTexture.push_back(&enemyTexture1);
	enemyTexture.push_back(&enemyTexture2);
	UIBG.loadFromFile("./Sprite/Object/UIbg.png");
	HowToPlayBG.loadFromFile("./Sprite/Object/UIHowToPlaybg.png");
	buttonBG.loadFromFile("./Sprite/Object/buttonBG.png");
	MENUtexture.loadFromFile("./Sprite/Background/MENUBG.png");
	/// Window ///
	sf::RenderWindow window(sf::VideoMode(1080, 720), "ULTRA CRATE BOX", sf::Style::Close);
	//variable
	bool isMoving = false, isLeft = false, isRight = true;
	// Platform //
	Wall1.loadFromFile("./Sprite/Map/Wall1.png");
	Floor1.loadFromFile("./Sprite/Map/Floor1.png");
	Platform1.loadFromFile("./Sprite/Map/Platform1.png");
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
	platforms.push_back(Platform(&Platform1, sf::Vector2f(300.0f, 25.0f), sf::Vector2f(540.0f, 580.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(350.0f, 25.0f), sf::Vector2f(203.0f, 240.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(350.0f, 25.0f), sf::Vector2f(203.0f, 480.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(350.0f, 25.0f), sf::Vector2f(877.0f, 240.0f)));
	platforms.push_back(Platform(&Platform1, sf::Vector2f(350.0f, 25.0f), sf::Vector2f(877.0f, 480.0f)));

	spawns.push_back(Platform(nullptr, sf::Vector2f(80.0f, 40.0f), sf::Vector2f(540.0f, 5.0f)));
	spawns.push_back(Platform(&deSpawn, sf::Vector2f(80.0f, 40.0f), sf::Vector2f(540.0f, 715.0f)));
	/// Sprite ///
	sf::Sprite BG_Color;
	sf::Sprite BG_Building;

	BG_Building.setTexture(BG_BuildingTexture);
	BG_Color.setTexture(BG_ColorTexture);

	// ANIMATION //
	Player player(&playerTexture, sf::Vector2u(5, 1), 0.135f, 200.0f, 140.0f);

	//Collider
	Collider playerCol = player.GetCollider();

	//Clock
	sf::Clock delayShootClock;
	sf::Clock delayEnemySpawnClock;
	sf::Clock deltaTimeClock;
	sf::Clock gameClock;
	sf::Clock escPauseClock;
	sf::Clock escGameClock;
	//Timer
	float delayEsc = 250.0f;
	float pauseTime = 0.0f;
	float delayShoot = 0.0f;
	float delayEnemySpawn = 0.0f;
	float enemyRespawnTimeClamp = 1500.0f;
	float deltaTime = 0.0f;
	float gameTime = 0.0f;

	//string
	std::string name;

	//variable
	int score = 0;
	int BGScrollMENU = 0;
	int cntFrame = 0;
	float padding = 33;

	//Text
	sf::Font font;
	font.loadFromFile("./Sprite/Font/PressStart2P-vaV7.ttf");

	//State
	State state;

	//Pause UI
	sf::RectangleShape pauseUIBG;
	pauseUIBG.setSize(sf::Vector2f(490.0f, 370.0f));
	pauseUIBG.setOrigin(pauseUIBG.getSize() / 2.0f);
	pauseUIBG.setPosition(540.0f, 360.0f);
	pauseUIBG.setTexture(&UIBG);

	//END_GAME UI
	sf::RectangleShape END_GAMEUIBG;
	END_GAMEUIBG.setSize(sf::Vector2f(490.0f, 370.0f));
	END_GAMEUIBG.setOrigin(pauseUIBG.getSize() / 2.0f);
	END_GAMEUIBG.setPosition(540.0f, 360.0f);
	END_GAMEUIBG.setTexture(&UIBG);

	//MENU UI
	sf::RectangleShape MENUBG;
	MENUBG.setSize(sf::Vector2f(1080, 720));
	MENUBG.setOrigin(MENUBG.getSize() / 2.0f);
	MENUBG.setPosition(540.0f, 360.0f);
	MENUBG.setTextureRect(sf::IntRect(0, 0, 1080, 720));
	MENUBG.setTexture(&MENUtexture);

	sf::RectangleShape LogoBorder;
	LogoBorder.setSize(sf::Vector2f(450, 270));
	LogoBorder.setOrigin(LogoBorder.getSize() / 2.0f);
	LogoBorder.setPosition(300.0f, 180.0f);
	LogoBorder.setTexture(&LogoBorderTexture);

	sf::RectangleShape Menu_Enemy1;
	Menu_Enemy1.setSize(sf::Vector2f(65.0f, 75.0f));
	Menu_Enemy1.setOrigin(Menu_Enemy1.getSize() / 2.0f);
	Menu_Enemy1.setPosition(350.0f, 250.0f);
	Menu_Enemy1.setTexture(enemyTexture[1]);
	Menu_Enemy1.setTextureRect(sf::IntRect(0, 0, enemyTexture[1]->getSize().x / 5, enemyTexture[1]->getSize().y));

	sf::RectangleShape Menu_Enemy2;
	Menu_Enemy2.setSize(sf::Vector2f(40.0f, 45.0f));
	Menu_Enemy2.setOrigin(Menu_Enemy1.getSize() / 2.0f);
	Menu_Enemy2.setPosition(470.0f, 280.0f);
	Menu_Enemy2.setTexture(enemyTexture[0]);
	Menu_Enemy2.setTextureRect(sf::IntRect(0, 0, enemyTexture[0]->getSize().x / 10, enemyTexture[0]->getSize().y));

	sf::RectangleShape Menu_Enemy3;
	Menu_Enemy3.setSize(sf::Vector2f(40.0f, 45.0f));
	Menu_Enemy3.setOrigin(Menu_Enemy1.getSize() / 2.0f);
	Menu_Enemy3.setPosition(420.0f, 280.0f);
	Menu_Enemy3.setTexture(enemyTexture[0]);
	Menu_Enemy3.setTextureRect(sf::IntRect((enemyTexture[0]->getSize().x / 10) * 2, 0, enemyTexture[0]->getSize().x / 10, enemyTexture[0]->getSize().y));

	sf::RectangleShape Menu_HighScore_BG;
	Menu_HighScore_BG.setSize(sf::Vector2f(500.0f, 300.0f));
	Menu_HighScore_BG.setOrigin(Menu_HighScore_BG.getSize() / 2.0f);
	Menu_HighScore_BG.setPosition(300.0f, 500.0f);
	Menu_HighScore_BG.setTexture(&UIBG);

	sf::RectangleShape Menu_HowToPlay_BG;
	Menu_HowToPlay_BG.setSize(sf::Vector2f(990.0f,660.0f));
	Menu_HowToPlay_BG.setOrigin(Menu_HowToPlay_BG.getSize() / 2.0f);
	Menu_HowToPlay_BG.setPosition(540.0f, 360.0f);
	Menu_HowToPlay_BG.setTexture(&HowToPlayBG);
	
	//Textbox
	Textbox textbox1(18, sf::Color::White, false, font, sf::Vector2f(710.0f, 250.0f));

	//HIGHSCORE
	std::vector<std::pair<int, std::string>> highScore;
	FILE* file;
	char temp[25];
	std::string nameArr[6];
	int scoreArr[6];
	bool collectHS = false;
	file = fopen("./highScore.txt", "r");
	for (int i = 0;i < 5;i++) {
		fscanf(file, "%s", temp);
		nameArr[i] = temp;
		fscanf(file, "%d", &scoreArr[i]);
		highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
	}

	//Sound
	bool playGameMusic = false;
	bool playMenuMusic = false;
	sf::SoundBuffer laserFiredBuffer;
	sf::Sound laserFiredSF;
	laserFiredBuffer.loadFromFile("./Soundtrack/laserGun.wav");
	laserFiredSF.setBuffer(laserFiredBuffer);
	laserFiredSF.setVolume(10);

	sf::SoundBuffer playerShootBuffer;
	sf::Sound playerShootSF;
	playerShootBuffer.loadFromFile("./Soundtrack/Shoot.wav");
	playerShootSF.setBuffer(playerShootBuffer);
	playerShootSF.setVolume(5);

	sf::SoundBuffer buttonHitBuffer;
	buttonHitBuffer.loadFromFile("./Soundtrack/bt.wav");

	sf::SoundBuffer enemyHitBuffer;
	sf::Sound enemyHitSF;
	enemyHitBuffer.loadFromFile("./Soundtrack/enemyHit.wav");
	enemyHitSF.setBuffer(enemyHitBuffer);
	enemyHitSF.setVolume(5);

	sf::SoundBuffer boxHitBuffer;
	sf::Sound boxHitSF;
	boxHitBuffer.loadFromFile("./Soundtrack/boxHit.wav");
	boxHitSF.setBuffer(boxHitBuffer);
	boxHitSF.setVolume(5);

	sf::Music gameMusic;
	gameMusic.openFromFile("./Soundtrack/InGameMusic.wav");
	gameMusic.setVolume(10);
	gameMusic.setLoop(true);

	sf::Music menuMusic;
	menuMusic.openFromFile("./Soundtrack/InMenuMusic.wav");
	menuMusic.setVolume(5);
	menuMusic.setLoop(true);

	//Button
	buttons.push_back(Button(sf::Vector2f(pauseUIBG.getOrigin().x + 180.0f, pauseUIBG.getOrigin().y + 285.0f), sf::Vector2f(180.0f, 70.0f), &font, "RESUME", &buttonBG, PAUSE, RESUME, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(pauseUIBG.getOrigin().x + 410.0f, pauseUIBG.getOrigin().y + 285.0f), sf::Vector2f(180.0f, 70.0f), &font, "EXIT", &buttonBG, PAUSE, EXIT, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(END_GAMEUIBG.getOrigin().x + 410.0f, END_GAMEUIBG.getOrigin().y + 285.0f), sf::Vector2f(195.0f, 70.0f), &font, "CONTINUE", &buttonBG, END_GAME, END_GAME_CONTINUE, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(830.0f, 360.0f), sf::Vector2f(280.0f, 100.0f), &font, "START", &buttonBG, MENU, MENU_START, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(830.0f, 480.0f), sf::Vector2f(280.0f, 100.0f), &font, "HIGHSCORE", &buttonBG, MENU, MENU_HIGHSCORE, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(917.5f, 600.0f), sf::Vector2f(110.0f, 100.0f), &font, "EXIT", &buttonBG, MENU, MENU_EXIT, &buttonHitBuffer));
	buttons.push_back(Button(sf::Vector2f(770.0f, 600.0f), sf::Vector2f(160.0f, 100.0f), &font, "TUTORIAL", &buttonBG, MENU, MENU_HOWTOPLAY, &buttonHitBuffer));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::TextEntered:
				textbox1.typedOn(event);
				break;
			}
		}
		state.Update();
		if (state.isCloseGame()) {
			window.close();
		}
		if (state.getGameState() == MENU) {
			if (!playMenuMusic) {
				menuMusic.play();
				gameMusic.stop();
				playMenuMusic = true;
				playGameMusic = false;
			}
			score = 0;
			gameClock.restart();
			if (state.isShowHighscore()) {
				if (!state.isPushButton()) {
					highScore.erase(highScore.begin(), highScore.end());
					file = fopen("./highScore.txt", "r");
					for (int i = 0;i < 5;i++) {
						fscanf(file, "%s", temp);
						nameArr[i] = temp;
						fscanf(file, "%d", &scoreArr[i]);
						highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
					}
					buttons.push_back(Button(sf::Vector2f(550.0f, 630.0f), sf::Vector2f(180.0f, 90.0f), &font, "CLOSE", &buttonBG, MENU, MENU_HIGHSCORE_EXIT, &buttonHitBuffer));
					state.setPushButton(true);
				}
			}
			if (state.isShowHowToPlay()) {
				if (!state.isPushButton()) {
					buttons.push_back(Button(sf::Vector2f(970.0f, 660.0f), sf::Vector2f(180.0f, 90.0f), &font, "CLOSE", &buttonBG, MENU, MENU_HOWTOPLAY_EXIT, &buttonHitBuffer));
					state.setPushButton(true);
				}
			}
		}
		if (state.getGameState() == PAUSE) {
			escGameClock.restart();
			state.setPauseTime(escPauseClock.getElapsedTime().asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escPauseClock.getElapsedTime().asMilliseconds() > delayEsc) {
				pauseTime = escPauseClock.getElapsedTime().asSeconds();
				for (Gun& gun : guns) {
					gun.setPauseTime(pauseTime);
				}
				player.setPauseTime(pauseTime);
				escPauseClock.restart();
				escGameClock.restart();
				state.setGameState(GAME);
			}
		}

		if (state.getGameState() == GAME) {
			collectHS = false;
			if (!playGameMusic) {
				gameMusic.play();
				menuMusic.stop();
				playGameMusic = true;
				playMenuMusic = false;
			}
			if (pauseTime != 0.0f)
				escPauseClock.restart();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escGameClock.getElapsedTime().asMilliseconds() > delayEsc) {
				escGameClock.restart();
				escPauseClock.restart();
				state.setGameState(PAUSE);
			}
			gameTime = gameClock.getElapsedTime().asSeconds();
			if (gameTime - pauseTime > 180.0f) {
				gameClock.restart();
				gameTime = 30000.0f;
			}
			deltaTime = deltaTimeClock.restart().asSeconds() - pauseTime;
			delayShoot = delayShootClock.getElapsedTime().asMilliseconds() - (pauseTime * 1000);
			delayEnemySpawn = delayEnemySpawnClock.getElapsedTime().asMilliseconds() - (pauseTime * 1000);
			if (deltaTime > 1.0f / 60.0f) {
				deltaTime = 1.0f / 60.0f;
			}
			sf::Vector2f direction;
			if (delayEnemySpawn > std::fmax(1300.0f, std::fmax((std::fmod(rand(), enemyRespawnTimeClamp + 1)), enemyRespawnTimeClamp)) && gameTime > 5.0f) {
				int temprand = rand() % 2;
				createEnemy(enemies, temprand, enemyTexture, gameTime);
				delayEnemySpawnClock.restart();
				if (enemyRespawnTimeClamp > 1300.0f) {
					enemyRespawnTimeClamp -= 5.0f;
				}
				if (enemyRespawnTimeClamp <= 1300.0f) {
					enemyRespawnTimeClamp = 1500.0f;
				}
			}
			player.Update(&playerTexture, deltaTime, gunTexture_R, &state);
			if (player.isShooting() && delayShoot > player.getShootDelayTime()) {
				if (player.GetGunType() == 0) {
					playerShootSF.setPitch(1.0f);
					playerShootSF.play();
				}
				if (player.GetGunType() == 1 && bullets.size() % 2 == 1) {
					playerShootSF.setPitch(1.2f);
					playerShootSF.play();
				}
				if (player.GetGunType() == 2) {
					playerShootSF.setPitch(0.5f);
					playerShootSF.play();
				}
				if (player.GetGunType() == 3) {
					laserFiredSF.play();
				}
				if (player.GetGunType() != 3) {
					bullets.push_back(Bullet(&bulletTexture, player.GetGunType(), player.isFaceRight(), player.GetGunPosition()));
				}
				else {
					bullets.push_back(Bullet(&laserTexture, player.GetGunType(), player.isFaceRight(), player.GetGunPosition()));
				}
				delayShootClock.restart();
			}
			updateBullet(bullets, deltaTime);
			updateEnemies(enemies, deltaTime, boxes, &boxTexture, score);
			updateBoxes(boxes, deltaTime, guns, gunTexture_R);
			updateGuns(guns, deltaTime, state);
			playerCollisionWithEnemy(enemies, player, playerCol, direction);
			if (spawns[1].GetCollider().CheckCollision(playerCol, direction, 1.0f)) {
				if (!player.isImmune()) {
					player.setIsImmune(true);
					player.changeHp(-1);
				}
			}
			for (int i = 0;i < boxes.size();i++) {
				Collider temp = boxes[i].GetCollider();
				bulletCollisionWithBoxes(bullets, boxes[i], temp, direction, &boxHitSF);
				boxCollisionWithPlatforms(platforms, boxes[i], temp, direction);
				boxCollisionWithPlatforms(walls, boxes[i], temp, direction);
			}
			for (int i = 0;i < enemies.size();i++) {
				if (!enemies[i].isDead()) {
					Collider temp = enemies[i].GetCollider();
					enemyCollisionWithPlatforms(walls, enemies[i], temp, direction);
					enemyCollisionWithPlatforms(platforms, enemies[i], temp, direction);
					bulletCollisionWithEnemies(bullets, enemies[i], temp, direction, &enemyHitSF);
				}
			}
			for (int i = 0;i < bullets.size();i++) {
				Collider temp = bullets[i].GetCollider();
				platformCollisionWithBullets(walls, bullets[i], temp, direction);
				platformCollisionWithBullets(platforms, bullets[i], temp, direction);
			}
			playerCollisionWithGuns(guns, player, playerCol, direction);
			playerCollisionWithPlatforms(walls, player, playerCol, direction);
			playerCollisionWithPlatforms(platforms, player, playerCol, direction);
			playerCollisionWithPlatforms(spawns, player, playerCol, direction);
		}
		window.clear();
		updateButtons(buttons, window, state.getGameState(), state);
		pauseTime = 0.0f;
		textbox1.Update(&state, sf::Mouse::getPosition(window));
		if (state.getGameState() == MENU) {
			cntFrame++;
			if (cntFrame >= 10) {
				BGScrollMENU += 1;
				cntFrame = 0;
			}
			drawMENU(MENUBG, buttons, window, state.getGameState(), &font, BGScrollMENU);
			window.draw(LogoBorder);
			showText(sf::Vector2f(125.0f, 85.0f), "ULTRA", &font, 62, window);
			showText(sf::Vector2f(180.0f, 155.0f), "CRATE", &font, 62, window);
			showText(sf::Vector2f(125.0f, 225.0f), "BOX", &font, 62, window);
			showText(sf::Vector2f(560.0f, 10.0f), "63011086 Isara Phadungprasertkul", &font, 16, window);
			window.draw(Menu_Enemy1);
			window.draw(Menu_Enemy2);
			window.draw(Menu_Enemy3);
			textbox1.Draw(window);
			showText(sf::Vector2f(690.0f, 200.0f), "INPUT YOUR NAME", &font, 18, window);
			if (state.isShowHighscore() && state.isPushButton()) {
				window.draw(Menu_HighScore_BG);
				showText(sf::Vector2f(100.0f, 395.0f), highScore[0].second, &font, 16, window);
				showText(sf::Vector2f(320.0f, 395.0f), std::to_string(highScore[0].first), &font, 16, window);
				showText(sf::Vector2f(100.0f, 445.0f), highScore[1].second, &font, 16, window);
				showText(sf::Vector2f(320.0f, 445.0f), std::to_string(highScore[1].first), &font, 16, window);
				showText(sf::Vector2f(100.0f, 495.0f), highScore[2].second, &font, 16, window);
				showText(sf::Vector2f(320.0f, 495.0f), std::to_string(highScore[2].first), &font, 16, window);
				showText(sf::Vector2f(100.0f, 545.0f), highScore[3].second, &font, 16, window);
				showText(sf::Vector2f(320.0f, 545.0f), std::to_string(highScore[3].first), &font, 16, window);
				showText(sf::Vector2f(100.0f, 595.0f), highScore[4].second, &font, 16, window);
				showText(sf::Vector2f(320.0f, 595.0f), std::to_string(highScore[4].first), &font, 16, window);
			}
			drawButtons(buttons, window, state.getGameState());
			if (state.isShowHowToPlay()) {
				window.draw(Menu_HowToPlay_BG);
			}
			for (Button& button : buttons) {
				if (button.isShowInGameState() == state.getGameState() && button.getType() == MENU_HOWTOPLAY_EXIT) {
					button.Draw(window);
				}
			}
		}
		if (state.getGameState() == GAME || state.getGameState() == PAUSE) {
			window.draw(BG_Color);
			window.draw(BG_Building);
			showText(sf::Vector2f(865.0f - (padding * std::to_string(score).size()), 25.0f), "SCORE:", &font, 32, window);
			showText(sf::Vector2f(1053.0f - (padding * std::to_string(score).size()), 25.0f), std::to_string(score), &font, 32, window);
			drawPlatform(walls, window);
			drawPlatform(platforms, window);
			drawBullet(bullets, window);
			drawButtons(buttons, window, state.getGameState());
			drawBoxes(boxes, window);
			drawGuns(guns, window);
			drawEnemies(enemies, window);
			spawns[1].Draw(window);
			player.Draw(window);
			if (state.getGameState() == PAUSE) {
				drawPAUSE(pauseUIBG, buttons, window, state.getGameState(), &font);
			}
			name = textbox1.getName();
		}
		if (state.getGameState() == END_GAME) {
			drawEND_GAME(END_GAMEUIBG, buttons, window, state.getGameState(), &font, score);
			player.restart();
			eraseEnemy(enemies);
			eraseGun(guns);
			eraseBox(boxes);
			eraseBullet(bullets);
			gameTime = 0.0f;
			gameClock.restart();
			textbox1.resetString();
			showText(sf::Vector2f(350.0f, 450.0f), "NAME:", &font, 16, window);
			showText(sf::Vector2f(350.0f, 480.0f), name, &font, 16, window);
			if (!collectHS) {
				highScore.erase(highScore.begin(), highScore.end());
				file = fopen("./highScore.txt", "r");
				for (int i = 0;i < 5;i++) {
					fscanf(file, "%s", temp);
					nameArr[i] = temp;
					fscanf(file, "%d", &scoreArr[i]);
					highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
				}
				if (name == "") {
					name = "NoName";
				}
				highScore.push_back(std::make_pair(score, name));
				std::sort(highScore.begin(), highScore.end());
				fclose(file);
				file = fopen("./highScore.txt", "w");
				char temp[26];
				for (int i = 5;i >= 1;i--) {
					strcpy(temp, highScore[i].second.c_str());
					fprintf(file, "%s %d\n", temp, highScore[i].first);
				}
				fclose(file);
				collectHS = true;
			}

		}
		window.display();
	}
	return 0;
}
void drawMENU(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font, int frame) {
	int speed = 2;
	UIBG.setTextureRect(sf::IntRect((int)speed * frame, 0, 1080, 720));

	window.draw(UIBG);
}
void playerCollisionWithEnemy(std::vector<Enemy>& vect, Player& player, Collider playerCol, sf::Vector2f direction) {
	for (Enemy& enemy : vect) {
		if (!player.isImmune()) {
			if (!enemy.isDead()) {
				if (enemy.GetCollider().CheckCollision(playerCol, direction, 1.0f)) {
					player.setIsImmune(true);
					if (enemy.getType() == 0) {
						player.changeHp(enemy.getDmg());
					}
					else if (enemy.getType() == 1) {
						player.changeHp(enemy.getDmg());
					}
				}
			}
		}
	}
}
void playerCollisionWithGuns(std::vector<Gun>& vect, Player& player, Collider col, sf::Vector2f direction) {
	for (Gun& gun : vect)
	{
		if (gun.GetCollider().CheckCollision(col, direction, 1.0f)) {
			player.setGunType(gun.GetGunType());
			gun.setPickUp(true);
		}
	}
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
		if (bullet.GetType() != 3) {
			if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
				bullet.setDestroy(true);
			}
		}
	}
}
void bulletCollisionWithEnemies(std::vector<Bullet>& vect, Enemy& enemy, Collider col, sf::Vector2f direction, sf::Sound* sound) {
	if (!enemy.isHit()) {
		for (Bullet& bullet : vect) {
			if (bullet.GetType() != 3) {
				if (bullet.GetCollider().CheckCollision(col, direction, 1.0f)) {
					sound->play();
					bullet.setDestroy(true);
					enemy.hitWithBullet(bullet);
				}
			}
			else {
				if (bullet.getTimeAlive() < 800.0f) {
					if (bullet.GetCollider().CheckCollision(col, direction, 1.0f)) {
						enemy.hitWithBullet(bullet);
					}
				}
			}
		}
	}
}
void bulletCollisionWithBoxes(std::vector<Bullet>& vect, Box& box, Collider col, sf::Vector2f direction, sf::Sound* sound) {
	for (Bullet& bullet : vect) {
		if (box.isOnGround()) {
			if (bullet.GetType() != 3) {
				if (bullet.GetCollider().CheckCollision(col, direction, 1.0f)) {
					bullet.setDestroy(true);
					box.hitWithBullet(bullet);
					sound->play();
				}
			}
			else {
				if (bullet.getTimeAlive() < 800.0f) {
					if (bullet.GetCollider().CheckCollision(col, direction, 1.0f)) {
						box.hitWithBullet(bullet);
					}
				}
			}
		}
	}
}
void boxCollisionWithPlatforms(std::vector<Platform>& vect, Box& box, Collider col, sf::Vector2f direction) {
	for (Platform& platform : vect) {
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f)) {
			box.OnCollision(direction);
			box.setIsOnGround(true);
		}
	}
}
void drawPlatform(std::vector<Platform>& vect, sf::RenderWindow& window) {
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
void drawGuns(std::vector<Gun>& vect, sf::RenderWindow& window) {
	for (Gun& gun : vect) {
		gun.Draw(window);
	}
}
void drawButtons(std::vector<Button>& vect, sf::RenderWindow& window, int gameState) {
	for (Button& button : vect) {
		if (button.isShowInGameState() == gameState && button.getType() != MENU_HOWTOPLAY_EXIT ) {
			button.Draw(window);
		}
	}
}
void updateButtons(std::vector<Button>& vect, sf::RenderWindow& window, int gameState, State& state) {
	for (Button& button : vect) {
		if (button.isShowInGameState() == gameState && !state.isShowHowToPlay()) {
			button.Update(sf::Mouse::getPosition(window), &state);
		}
		else if (button.isShowInGameState() == gameState && state.isShowHowToPlay() && button.getType() == MENU_HOWTOPLAY_EXIT) {
			button.Update(sf::Mouse::getPosition(window), &state);
		}
	}
	for (int i = 0;i < vect.size();i++) {
		if (!state.isShowHighscore()) {
			if (vect[i].getType() == MENU_HIGHSCORE_EXIT) {
				vect.erase(vect.begin() + i);
			}
		}
	}
	for (int i = 0;i < vect.size();i++) {
		if (!state.isShowHowToPlay()) {
			if (vect[i].getType() == MENU_HOWTOPLAY_EXIT) {
				vect.erase(vect.begin() + i);
			}
		}
	}
}
void updateBullet(std::vector<Bullet>& vect, float deltaTime) {
	for (Bullet& bullet : vect) {
		bullet.Update(deltaTime);
		if (bullet.getTimeAlive() > 300.0f && bullet.GetType() == 3) {
			bullet.setDestroy(true);
		}
	}
	for (int i = 0;i < vect.size();i++) {
		if (vect[i].isDestroy()) {
			vect.erase(vect.begin() + i);
		}
	}
}
void updateEnemies(std::vector<Enemy>& vect, float deltaTime, std::vector<Box>& vectBox, sf::Texture* texture, int& score) {
	for (Enemy& enemy : vect) {
		enemy.Update(deltaTime);
	}
	srand(time(0));
	for (int i = 0;i < vect.size();i++) {
		if (vect[i].getHp() <= 0) {
			if (!vect[i].isAlreadySpawnBox()) {
				vect[i].spawnBox();
				if (vect[i].isSpawnBox()) {
					vectBox.push_back(Box(texture, vect[i].GetPosition(), vect[i].getSpawnBoxInt() + rand()));
				}
				score += vect[i].getScore();
				if (vect[i].getTimeAlive() / 1000 <= 10) {
					score += 10 - (vect[i].getTimeAlive() / 1000);
				}
				vect[i].alreadySpawnBox(true);
			}

		}
		if (vect[i].GetPosition().y >= 720) {
			vect.erase(vect.begin() + i);
		}
	}
}
void updateBoxes(std::vector<Box>& vect, float deltaTime, std::vector<Gun>& gunVect, std::vector<sf::Texture*> gunTexture) {
	for (Box& box : vect) {
		box.Update(deltaTime);
	}
	for (int i = 0;i < vect.size(); i++) {
		if (vect[i].isDesttoy()) {
			Collider temp = vect[i].GetCollider();
			gunVect.push_back(Gun(vect[i].GetGunType(), temp, gunTexture));
			vect.erase(vect.begin() + i);
		}
	}
}
void createEnemy(std::vector<Enemy>& vect, int type, std::vector<sf::Texture*> texture, float gameTime) {
	srand(time(NULL));
	int salt1 = rand();
	srand(salt1);
	int salt2 = rand();
	srand(salt2);
	int salt3 = rand();
	srand(salt3);
	int ran = rand() + 1;
	srand(ran + 1);
	int ran1 = rand() + 1;
	int moder = 0;
	if (gameTime < 60.0f) {
		moder = 2;
	}
	else moder = 10;
	switch (ran % 3) {
	case 0:
		switch (ran % moder) {
		case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 9:case 8:
			vect.push_back(Enemy(texture[0], sf::Vector2u(11, 1), sf::Vector2f(530, 0), 0.095f, ran % moder, ran));
			break;
		case 2:
			vect.push_back(Enemy(texture[1], sf::Vector2u(5, 1), sf::Vector2f(530, 0), 0.095f, ran % moder, ran));
			break;
		}
		break;
	case 1:
		switch (ran % moder) {
		case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 9:case 8:
			vect.push_back(Enemy(texture[0], sf::Vector2u(11, 1), sf::Vector2f(550, 0), 0.095f, ran % moder, ran));
			break;
		case 2:
			vect.push_back(Enemy(texture[1], sf::Vector2u(5, 1), sf::Vector2f(550, 0), 0.095f, ran % moder, ran));
			break;
		}
		break;
	case 2:
		switch (ran % moder) {
		case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 9:case 8:
			vect.push_back(Enemy(texture[0], sf::Vector2u(11, 1), sf::Vector2f(530, 0), 0.095f, ran % moder, ran));
			break;
		case 2:
			vect.push_back(Enemy(texture[1], sf::Vector2u(5, 1), sf::Vector2f(530, 0), 0.095f, ran % moder, ran));
			break;
		}
		switch (ran1 % moder) {
		case 0:case 1:case 3:case 4:case 5:case 6:case 7:case 9:case 8:
			vect.push_back(Enemy(texture[0], sf::Vector2u(11, 1), sf::Vector2f(550, 0), 0.095f, ran1 % moder, ran1));
			break;
		case 2:
			vect.push_back(Enemy(texture[1], sf::Vector2u(5, 1), sf::Vector2f(550, 0), 0.095f, ran1 % moder, ran1));
			break;
		}
		break;
	}
}
void updateGuns(std::vector<Gun>& vect, float deltaTime, State& state) {
	for (int i = 0; i < vect.size(); i++) {
		for (Gun& gun : vect) {
			gun.Update(deltaTime, &state);
		}
		if (vect[i].isPickUp() || vect[i].isDestroy()) {
			vect.erase(vect.begin() + i);
		}
	}
}
void showText(sf::Vector2f position, std::string word, sf::Font* font, int size, sf::RenderWindow& window) {
	sf::Text text;
	text.setFont(*font);
	text.setPosition(position);
	text.setString(word);
	text.setCharacterSize(size);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3);
	window.draw(text);
}
void drawPAUSE(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font) {
	window.draw(UIBG);
	showText(sf::Vector2f(UIBG.getPosition().x - 105.0f, UIBG.getPosition().y - 90.0f), "PAUSE", font, 48, window);
	drawButtons(vect, window, gameState);
}
void drawEND_GAME(sf::RectangleShape UIBG, std::vector<Button>& vect, sf::RenderWindow& window, int gameState, sf::Font* font, int score) {
	window.draw(UIBG);
	showText(sf::Vector2f(UIBG.getPosition().x - 115.0f, UIBG.getPosition().y - 110.0f), "SCORE", font, 48, window);
	showText(sf::Vector2f(UIBG.getPosition().x - (15 * std::to_string(score).size()), UIBG.getPosition().y - 40.0f), std::to_string(score), font, 36, window);
	drawButtons(vect, window, gameState);
}
void eraseEnemy(std::vector<Enemy>& vect) {
	vect.erase(vect.begin(), vect.end());
}
void eraseBox(std::vector<Box>& vect) {
	vect.erase(vect.begin(), vect.end());
}
void eraseGun(std::vector<Gun>& vect) {
	vect.erase(vect.begin(), vect.end());
}
void eraseBullet(std::vector<Bullet>& vect) {
	vect.erase(vect.begin(), vect.end());
}