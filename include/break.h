#ifndef BREAK_H
#define BREAK_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



class Break
{
public:
	//Constructeur
	Break();

	//Accesseur

	//Mutateur
	void setTilePosition(Vector2f newPosition);
	void setTotalTime(float totalTime);

	//Méthodes
    void drawBreaking(RenderWindow& window, Clock clock);
	void restartClock(float totalTime);
	void setInvisible(RenderWindow& window);

	//Destructeur
	~Break(){}

private:
    int frameNumber, frameMax;
	float frameTimer, timeBetween2Frames;
	Clock breakClock;
	Sprite breakSprite;
	Vector2f breakPosition;
	Texture breakTexture;
	static const int TILE_SIZE = 16;
};
#endif