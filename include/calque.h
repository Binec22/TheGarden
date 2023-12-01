#ifndef CALQUE_H
#define CALQUE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "tuile.h"
#include "rock.h"
#include "grass.h"
#include "plant.h"
#include "farmland.h"
#include "item.h"

using namespace std;
using namespace sf;



class Calque
{
public:
	vector < vector < Tile *> > tuiles;
	int width, height;
	vector < vector < int > > values;
	Texture calqueTexture;
	Image imageCalque;

	//Constructeur
	Calque(int calqueNumber);

	//Accesseur
	Image getImage(void);

	//Mutateur
	void setImage(Image image);
	Calque& operator=(const Calque& newCalque);


	//Méthodes
	void setUpTiles(RenderWindow &window, const View& view);
	void drawPlants(RenderWindow &window, const View& view, float &currentTime);

	//Destructeur
	~Calque();
private :

	void selectCalque();
	void readCSV();
	void constructCalque();

	int calqueNumber;
	int tilesByLine;
	string	fileName;
	string calqueTextureName;
	const int TILE_SIZE = 16;
	
};
#endif