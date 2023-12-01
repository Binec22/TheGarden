#include "grass.h"

Texture Grass::grassTexture;

Grass::Grass(Vector2f &tilePosition, int &valeur) : Tile(grassTexture, tilePosition, valeur)
{
}

void Grass::initializeGrassTexture(Texture &texture)
{
    grassTexture = texture;
}

