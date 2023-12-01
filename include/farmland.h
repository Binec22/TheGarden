#ifndef FARMLAND_H
#define FARMLAND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tuile.h"

using namespace sf;
using namespace std;

class Farmland : public Tile
{
public :
    Farmland(Vector2f tilePosition,int valeur);
	static void initializeFarmlandTexture(Texture& texture);
	virtual void drawBreaking(RenderWindow& window){}
	~Farmland(){}
private:
	static Texture farmlandTexture;
};


#endif