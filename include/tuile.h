#ifndef TUILE_H
#define TUILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



class Tile
{
public:
	//Constructeur
	Tile(Vector2f& tilePosition, int& valeur);
	Tile(Texture& spriteTexture,Vector2f& tilePosition,int& valeur);
	Tile(Texture& spriteTexture,Vector2f& tilePosition,int& valeur, float miningDuration);

	//Accesseur
    int getValeur(void);
	float getMiningDuration(void);
	Vector2f getTilePosition(void);
	Sprite getTileSprite(void);
	Texture getTileTexture(void);
	virtual int getMaturity(void); //Pour les plantes
	virtual bool isMature(void); //Pour les plantes

	//Mutateur
    void setValeur(int valeur);
	void setMiningDuration(float newDuration);
	void setTilePosition(Vector2f newPosition);
	void setTileSprite(Texture texture);
	void setTileSprite(IntRect textRect);
	void setTileTexture(Texture newTexture);

	//Méthodes
	bool setUpSprite(string textureName);
	Tile& operator=(const Tile& other);
	virtual void updateMaturity(float currentTime); //Pour les plantes;

	//Destructeur
	virtual ~Tile();

protected:
	int valeur;
	float miningDuration;
	Sprite sprite;
	Vector2f tilePosition;
	Texture spriteTexture;
	static const int TILE_SIZE = 16;
};
#endif