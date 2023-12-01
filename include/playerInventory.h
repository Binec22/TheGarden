#ifndef PLAYERINVENTORY_H
#define PLAYERINVENTORY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"
#include "item.h"

using namespace std;
using namespace sf;

class PlayerInventory : public Inventory
{
public:
    // Constructeur
    PlayerInventory(int capacity);
    virtual ~PlayerInventory();

    // Accesseurs
    int getSelectedItem();
    int getSelectedNum(Input &input);

    // Mutateurs
    void updateSelectedItem(Input& input);
    
    // Méthodes
    
    bool recolt(const int itemType);
    void drawInventory(RenderWindow& window, View &view);
    void drawInShopInventory(RenderWindow &window, View &view);
    void drawHotbar(RenderWindow& window, View &view, Input& input);
    void handleClick(RenderWindow &window, View &view, Input &input);


protected:
    virtual void initialize() override;
    virtual void loadTextures() override;

private:
    // Spritesheet
    Texture inventoryTexture;
    Sprite inventorySprite;

    Texture hotbarTexture;
    Sprite hotbarSprite;

    Texture hightlightTexture;
    Sprite hightlightSprite;
};

#endif // PLAYERINVENTORY_H
