#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum ItemTypes {DEFAULT = 0, PICKAXE, AXE, SICKLE, HOE, STONE, WOOD, FLOWER, WHEAT, ONE_GOLD, TEN_GOLD, HUNDRED_GOLD, BEETROOT_SEED, BEETROOT, POTATOE_SEED, POTATOE};

class Item
{
public:
    Item(const int type);
    Item(const int type, int amount);

    virtual ~Item();

    //Accesseurs
    const int& getAmount();
    int getType() const;
    Vector2f getTilePosition(void);
	Sprite getSprite(void);
	Texture getTexture(void);
    const bool isStackable() const;

    //Mutateurs
    void setAmount(const int amount);
    void updateAmount(const int amount);
    void setType(int type);
	void setPosition(Vector2f newPosition);
	void setSprite(Texture texture);
	void setTexture(Texture newTexture);

    // Méthodes
    Item* clone();
    void initVariables();
    void loadTexture(const int type);
    void drawItem(RenderWindow &window);

    Image itemImage;
    Texture itemTexture;
    Sprite itemSprite;

private :
    // Variables
    int type;
    bool stackable;
    int amount;

    Vector2f position;



    const int TILE_SIZE = 16;
    const int TILES_BY_LINE = 16;

};


#endif