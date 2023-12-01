#include "rock.h"

Texture Rock::rockTexture;

Rock::Rock(Vector2f &tilePosition, int &valeur) : Tile(rockTexture, tilePosition, valeur)
{
    setMiningDuration(700.0f);
}

void Rock::initializeRockTexture(Texture &texture)
{
    rockTexture = texture;
}

