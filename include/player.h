#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "input.h"
#include "calque.h"
#include "utilitaire.h"
#include "break.h"
#include "playerInventory.h"
#include "sellerInventory.h"

using namespace std;
using namespace sf;


class Player
{
// Structure
struct Tool { bool hand, pickaxe, axe, hoe, sickle;};

public:
	//Constructeur
	Player();
	~Player();
	PlayerInventory* inventory;
	
	//Accesseurs
	Vector2i getPlayerPosition(void);
	int getGoldAmount(void);

	//Mutateurs
	void setGoldAmout(int amout);
	void addGold(int amout);
	void removeGold(int amout);


	//Méthodes
	void drawPlayer(RenderWindow &window);
	void updatePlayer(Input &input, Calque &calqueDeco, Calque &calqueSol, Calque &calquePlants, RenderWindow &window);
	
	bool checkShop(RenderWindow &window, Input &input, FloatRect shopRect, Vector2f sellerPosition);
	bool checkTile(Calque &calque, RenderWindow &window);
	void destroyTile(Calque &calque, RenderWindow &window, int tool);
	void plant(Calque &calqueSol, Calque &calquePlants, RenderWindow &window, int seedType);
	void recoltPlant(Calque &calquePlants, RenderWindow &window, int plantType);
	void buy(int index, SellerInventory &sellerInventory, float currentTime);
	
	

private:
	void loadTexture();
	void initVariables();
	void initStuff();

	//Vector2f playerPosition;
	int x, y;	// Coordonnées du sprite
	int h, w;	// Largeur, hauteur du sprite
	int direction;
	int etat;

	int gold;
	float lastBuyTime;

	int selectedItem;

	Break breaking;
	Tool tool;

	int frameNumber, frameTimer, frameMax;	// Numéro de la frame (= image) en cours + timer

	int saveX, saveY;	//Sauvegarde des coordonnées de départ

	//Spritesheet
	Texture farmerTexture;
	Sprite farmer;

	//Mining timer
	Clock miningClock;
	const float MINING_DURATION = 1000.0f; // en ms
	bool mouseNotChanged;

	//Constantes

	// Constante pour l'animation
	const int  TIME_BETWEEN_2_FRAMES_PLAYER = 4;

	// Taille du sprite du personnage (largeur = width et hauteur = heigth) 
	const int  PLAYER_WIDTH = 16;
	const int  PLAYER_HEIGTH = 18;

	//Vitesse de déplacement en pixels du sprite
	const int  PLAYER_SPEED = 4;

	const int LEFT = 1;

	//Valeurs attribuées aux états/directions
	const int WALK_DOWN = 0;
	const int WALK_UP = 1;
	const int WALK_LEFT = 2;
	const int WALK_RIGHT = 3;

	const float SHOP_COOLDOWN = 200.0f; // en ms

};
#endif