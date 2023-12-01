#ifndef ROCK_H
#define ROCK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tuile.h"

using namespace sf;
using namespace std;

class Rock : public Tile
{
public :
    Rock(Vector2f& tilePosition,int& valeur);
	static void initializeRockTexture(Texture& texture);
	virtual void drawBreaking(RenderWindow& window){}
	~Rock(){}
private:
   	//static Sprite rockSprite;
	static Texture rockTexture;
};


#endif