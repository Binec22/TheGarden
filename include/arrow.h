#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



class Arrow
{
public:
	//Constructeur
	Arrow();

	//Accesseur

	//Mutateur
	void setTilePosition(Vector2f newPosition);

	//Méthodes
    void drawArrow(RenderWindow& window, float currentTime);

	//Destructeur
	~Arrow(){}

private:
    int frameNumber, frameMax, line, row;
	float frameTimer, timeBetween2Frames, lastFrameTime;
	Sprite arrowSprite;
	Vector2f arrowPosition;
	Texture arrowTexture;
	static const int ARROW_WIDTH = 28;
	static const int ARROW_HEIGHT = 21;
};
#endif