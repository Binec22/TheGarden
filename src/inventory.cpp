#include "inventory.h"

Inventory::Inventory(int capacity)
{
    this->capacity = capacity;
    this->font.loadFromFile("graphics/Minecraft.ttf");
}

Inventory::~Inventory()
{
    this->freeMemory();
}

const int &Inventory::size() const
{
    return this->nbOfItems;
}

const int &Inventory::maxSize() const
{
    return this->capacity;
}

int Inventory::getItemType(const int index)
{
    if(this->itemArray[index] != nullptr)
        return this->itemArray[index]->getType();
    else
        return DEFAULT;
}

int Inventory::getItemAmount(const int index)
{
    return this->itemArray[index]->getAmount();
}

int Inventory::findItem(const int type)
{
    for (int i = 0; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr && this->itemArray[i]->getType() == type)
            return i;
    }
    return NULL_INT;
}

void Inventory::clear()
{
    for (int i = 0; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr)
            delete this->itemArray[i];
    }
    this->nbOfItems = 0;

    this->nullify();
}

bool Inventory::empty() const
{
    return this->nbOfItems == 0;
}

bool Inventory::add(Item *item)
{
    if(this->nbOfItems < this->capacity)
    {
        int index = 0;
        while(this->itemArray[index] != nullptr)
        {
            index++;
        }
        this->itemArray[index] = item->clone();;
        this->nbOfItems++;
        return true;
    }
    return false;
}

bool Inventory::remove(const int index)
{
    if(this->nbOfItems > 0)
    {
        if(index < 0 || index >= this->capacity)
            return false;

        delete this->itemArray[index];
        this->itemArray[index] = nullptr;
        this->nbOfItems--;
        return true;
    }
    return false;
}

bool Inventory::contain(const int itemType)
{
    for(int i = 0; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr && this->itemArray[i]->getType() == itemType)
            return true;
    }
    return false;
}

bool Inventory::containAmount(const int itemType, const int montant)
{
    for(int i = 0; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr && this->itemArray[i]->getType() == itemType && this->itemArray[i]->getAmount() >= montant)
            return true;
    }
    return false;
}

void Inventory::updateItem(int index, int montant)
{
    this->itemArray[index]->updateAmount(montant);
    if(this->itemArray[index]->getAmount() <= 0)
    {
        delete this->itemArray[index];
        this->itemArray[index] = nullptr;
        this->nbOfItems--;
    }
}

void Inventory::nullify(const int from)
{
    for (int i = from; i < this->capacity; i++)
    {
        this->itemArray[i] = nullptr;
    }
}

void Inventory::freeMemory()
{
    for (int i = 0; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr)
            delete this->itemArray[i];
    }
    delete[] this->itemArray;
}
