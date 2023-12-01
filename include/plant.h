#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tuile.h"

using namespace sf;
using namespace std;

class Plant : public Tile
{
public :
    Plant(Vector2f plantPosition, int valeur);

    virtual int getMaturity();

    virtual bool isMature();

    static void loadPlantImage(Texture &texture);
    virtual void updateMaturity(float currentTime);

	~Plant();
private:
    static Texture plantTexture;
    int totalGrowthStep;
    int growthStepLeft;
    float timeBetweenTwoSteps;
    float lastGrowthTime;
    bool mature;
};


#endif