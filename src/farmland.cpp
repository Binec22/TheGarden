#include "farmland.h"

Texture Farmland::farmlandTexture;

Farmland::Farmland(Vector2f tilePosition, int valeur) : Tile(farmlandTexture, tilePosition, valeur)
{
}

void Farmland::initializeFarmlandTexture(Texture &texture)
{
    farmlandTexture = texture;
}

