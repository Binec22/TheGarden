#include "seller.h"

Seller::Seller()
{
	//Chargement du spritesheet
	if (!this->sellerTexture.loadFromFile("graphics/seeds.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement du spritesheet." << endl;
	}
	else
		this->sellerSprite.setTexture(this->sellerTexture);
	
	this->sellerInventory = new SellerInventory(22);
	this->initShop();
	
}

Seller::~Seller()
{
}

void Seller::initShop()
{
	this->sellerInventory->add(new Item(STONE,1));
	this->sellerInventory->add(new Item(ONE_GOLD,1));
	this->sellerInventory->add(new Item(WOOD,2));
	this->sellerInventory->add(new Item(ONE_GOLD,1));
	this->sellerInventory->add(new Item(WHEAT,5));
	this->sellerInventory->add(new Item(ONE_GOLD,1));
	this->sellerInventory->add(new Item(TEN_GOLD, 1));
	this->sellerInventory->add(new Item(BEETROOT_SEED, 30));
	this->sellerInventory->add(new Item(TEN_GOLD, 1));
	this->sellerInventory->add(new Item(POTATOE_SEED, 30));
	this->sellerInventory->add(new Item(BEETROOT, 30));
	this->sellerInventory->add(new Item(HUNDRED_GOLD, 1));
	this->sellerInventory->add(new Item(POTATOE, 30));
	this->sellerInventory->add(new Item(HUNDRED_GOLD, 1));
	this->sellerInventory->add(new Item(ONE_GOLD, 10));
	this->sellerInventory->add(new Item(TEN_GOLD, 1));
	this->sellerInventory->add(new Item(TEN_GOLD, 10));
	this->sellerInventory->add(new Item(HUNDRED_GOLD, 1));
	this->sellerInventory->add(new Item(TEN_GOLD, 1));		
	this->sellerInventory->add(new Item(ONE_GOLD, 10));
	this->sellerInventory->add(new Item(HUNDRED_GOLD, 1));
	this->sellerInventory->add(new Item(TEN_GOLD, 10));	
}

void Seller::drawSeller(RenderWindow &window)
{
	this->sellerSprite.setPosition(880,775);
	window.draw(this->sellerSprite);
}
