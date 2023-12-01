#include "plant.h"

Texture Plant::plantTexture;


Plant::Plant(Vector2f plantPosition, int valeur) : Tile(plantTexture,plantPosition, valeur)
{
    this->lastGrowthTime = 0.0f;
    this->totalGrowthStep = 5;
    this->growthStepLeft = this->totalGrowthStep;
    this->timeBetweenTwoSteps = 10000.0f;
    this->mature = false;
}

int Plant::getMaturity()
{
    return this->growthStepLeft;
}

bool Plant::isMature()
{
    return this->mature;
}

void Plant::loadPlantImage(Texture &texture)
{
    plantTexture = texture;
}

void Plant::updateMaturity(float currentTime)
{
    if(!this->isMature())
    {
        if(currentTime - this->lastGrowthTime < this->timeBetweenTwoSteps)
        {
            return;
        }
        this->lastGrowthTime = currentTime;
        this->growthStepLeft--;
        if (this->growthStepLeft == 0)
        {
            this->mature = true;
        }
    }
}

Plant::~Plant()
{
}
