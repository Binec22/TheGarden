#ifndef SELLER_H
#define SELLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "input.h"
#include "player.h"
#include "sellerInventory.h"

using namespace std;
using namespace sf;


class Seller
{
public:
    SellerInventory* sellerInventory;

	//Constructeur
	Seller();
	~Seller();
	
	//Accesseurs

	//Méthodes
    void initShop();
	void drawSeller(RenderWindow &window);
	
	Sprite sellerSprite;
private:
	//Spritesheet
	Texture sellerTexture;
	

    
};
#endif