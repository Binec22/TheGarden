#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "input.h"

using namespace std;
using namespace sf;

const int NULL_INT = 260202;

class Inventory
{
public:
    Inventory(int capacity);
    virtual ~Inventory();

    // Accesseurs
    const int& size() const;
    const int& maxSize() const;
    int getItemType(const int index);
    int getItemAmount(const int index);
    int findItem(const int type);


    //Méthodes
    void clear();
    bool empty() const;
    bool add(Item* item);
    bool remove(const int index);
    bool contain(const int itemType);
    bool containAmount(const int itemType, const int montant);
    void updateItem(int index, int montant);
    
    
protected:
    Item** itemArray;
    int nbOfItems;
    int capacity;
    int selectedItem;

    Font font;

    virtual void initialize() = 0;
    virtual void loadTextures() = 0;
    void nullify(const int from = 0);
    void freeMemory();
};

#endif
