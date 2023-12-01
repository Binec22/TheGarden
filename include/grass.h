#ifndef GRASS_H
#define GRASS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tuile.h"

using namespace sf;
using namespace std;

class Grass : public Tile
{
public :
    Grass(Vector2f& tilePosition,int& valeur);
	static void initializeGrassTexture(Texture& texture);
	virtual void drawBreaking(RenderWindow& window){}
	~Grass(){}
private:
	static Texture grassTexture;
};


#endif