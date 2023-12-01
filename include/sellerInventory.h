#ifndef SELLERINVENTORY_H
#define SELLERINVENTORY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"
#include "input.h"
#include "item.h"
#include "arrow.h"

using namespace std;
using namespace sf;

class SellerInventory : public Inventory
{
public:
	//Constructeur
	SellerInventory(int capacity);
	~SellerInventory();

	//Méthodes
	void drawSellerInventory(RenderWindow &window, View &view);
	void drawArrow(RenderWindow &window, View &view, float currentTime);
	int handleClick(RenderWindow &window, View &view, Input &input);

protected:
    virtual void initialize() override;
    virtual void loadTextures() override;

private:
	void initArrows();
	//Spritesheet
	Texture shopTexture;
	Sprite shopSprite;
	Arrow** arrowArray;
};
#endif