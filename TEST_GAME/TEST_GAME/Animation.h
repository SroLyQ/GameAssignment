#pragma once
#include "Initial.h"
class Animation
{
public:
	Animation(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);
	~Animation();

	void Update(float deltaTime,bool faceRight);

	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

