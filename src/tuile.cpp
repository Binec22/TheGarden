#include "tuile.h"

Tile::Tile(Vector2f &tilePosition, int &val)
{
    valeur = val;
    sprite.setPosition(tilePosition);
    miningDuration = 1000.0f;
}

Tile::Tile(Texture &texture, Vector2f &tilePosition, int &val)
{
    valeur = val;
    setTileSprite(texture);
    sprite.setPosition(tilePosition);
    miningDuration = 1000.0f;
}

Tile::Tile(Texture &texture, Vector2f &tilePosition, int &val, float miningDuration)
{
    valeur = val;
    setTileSprite(texture);
    sprite.setPosition(tilePosition);
    this->miningDuration = miningDuration;
}

int Tile::getValeur(void)
{
    return valeur;
}

float Tile::getMiningDuration(void)
{
    return miningDuration;
}

Vector2f Tile::getTilePosition(void)
{
    return tilePosition;
}

Sprite Tile::getTileSprite(void)
{
    return sprite;
}

Texture Tile::getTileTexture(void)
{
    return spriteTexture;
}

int Tile::getMaturity(void)
{
    return 0;
}

bool Tile::isMature(void)
{
    return false;
}

void Tile::setValeur(int val)
{
    valeur = val;
}

void Tile::setMiningDuration(float newDuration)
{
    miningDuration = newDuration;
}

void Tile::setTilePosition(Vector2f newPosition)
{
    tilePosition = newPosition;
}

void Tile::setTileSprite(Texture texture)
{
    spriteTexture = texture;
    sprite.setTexture(spriteTexture);
}

void Tile::setTileSprite(IntRect textRect)
{
    sprite.setTextureRect(textRect);
}

void Tile::setTileTexture(Texture newTexture)
{
    spriteTexture = newTexture;
}

bool Tile::setUpSprite(string textureName)
{
    if (!spriteTexture.loadFromFile(textureName))
        return false;
    sprite.setTexture(spriteTexture);
    return true;
}

Tile &Tile::operator=(const Tile &other)
{
    if (this != &other)
    {
        valeur = other.valeur;
        sprite = other.sprite;
        tilePosition = other.tilePosition;
        spriteTexture = other.spriteTexture;
    }
    return *this;
}

void Tile::updateMaturity(float currentTime)
{
}

Tile::~Tile()
{
}
