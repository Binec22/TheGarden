#include "item.h"

Item::Item(const int type)
{
    this->type = type;
    if(type == PICKAXE || type == AXE || type == HOE || type == SICKLE)
    {       
        this->stackable = false;
        this->amount = 1;
    }
    else
    {
        this->stackable = true;
        this->amount = 1;
    }
    if(!itemImage.loadFromFile("graphics/items.png"))
        cout << "Erreur lors du chargement de la texture des items" << endl;

    this->loadTexture(type);
}

Item::Item(const int type, int amount)
{
    this->type = type;
    if(type == PICKAXE || type == AXE || type == HOE || type == SICKLE)
    {       
        this->stackable = false;
        this->amount = amount;
    }
    else
    {
        this->stackable = true;
        this->amount = amount;
    }
    if(!itemImage.loadFromFile("graphics/items.png"))
        cout << "Erreur lors du chargement de la texture des items" << endl;

    this->loadTexture(type);
}

Item::~Item()
{
}

const int &Item::getAmount()
{
    return this->amount;
}

int Item::getType() const
{
return this->type;
}

Vector2f Item::getTilePosition(void)
{
    return this->position;
}

Sprite Item::getSprite(void)
{
    return this->itemSprite;
}

Texture Item::getTexture(void)
{
    return this->itemTexture;
}

const bool Item::isStackable() const
{
    return this->stackable;
}

void Item::setAmount(const int amount)
{
    this->amount = amount;
}

void Item::updateAmount(const int amount)
{
    this->amount = this->amount + amount;
}

void Item::setType(int type)
{
    this->type = type;
}

void Item::setPosition(Vector2f newPosition)
{
    this->position = newPosition;
}

void Item::setSprite(Texture texture)
{
    this->itemTexture = texture;
    this->itemSprite.setTexture(this->itemTexture);
}

void Item::setTexture(Texture newTexture)
{
    this->itemTexture = newTexture;
}

Item *Item::clone()
{
    return new Item(*this);
}

void Item::loadTexture(const int type)
{
    switch (type)
    {
    case PICKAXE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((176 % TILES_BY_LINE * TILE_SIZE) , (176 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;

    case AXE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((179 % TILES_BY_LINE * TILE_SIZE) , (179 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;

    case HOE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((180 % TILES_BY_LINE * TILE_SIZE) , (180 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;

    case SICKLE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((194 % TILES_BY_LINE * TILE_SIZE) , (194 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;

    case STONE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((18 % TILES_BY_LINE * TILE_SIZE) , (18 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;

    case WOOD:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((17 % TILES_BY_LINE * TILE_SIZE) , (17 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    
    case WHEAT:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((97 % TILES_BY_LINE * TILE_SIZE) , (97 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case ONE_GOLD:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((0 % TILES_BY_LINE * TILE_SIZE) , (0 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case TEN_GOLD:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((1 % TILES_BY_LINE * TILE_SIZE) , (1 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case HUNDRED_GOLD:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((2 % TILES_BY_LINE * TILE_SIZE) , (2 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case FLOWER:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((110 % TILES_BY_LINE * TILE_SIZE) , (110 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case BEETROOT_SEED:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((189 % TILES_BY_LINE * TILE_SIZE) , (189 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case BEETROOT:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((109 % TILES_BY_LINE * TILE_SIZE) , (109 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case POTATOE_SEED:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((222 % TILES_BY_LINE * TILE_SIZE) , (222 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    case POTATOE:
        this->itemTexture.loadFromImage(this->itemImage, IntRect((221 % TILES_BY_LINE * TILE_SIZE) , (221 / TILES_BY_LINE * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        this->itemSprite.setTexture(itemTexture);
        break;
    
    default:
        break;
    }
}

void Item::drawItem(RenderWindow &window)
{
}
