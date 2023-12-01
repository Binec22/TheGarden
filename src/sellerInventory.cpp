#include "sellerInventory.h"

SellerInventory::SellerInventory(int capacity) : Inventory(capacity)
{
    this->initialize();
    this->loadTextures();
}

SellerInventory::~SellerInventory()
{
    for (int i = 0; i < this->capacity/2; i++)
    {
        delete this->arrowArray[i];
    }
    delete[] this->arrowArray;
}

void SellerInventory::drawSellerInventory(RenderWindow &window, View &view)
{
    this->shopSprite.setPosition(view.getCenter().x-210, view.getCenter().y-280);
    window.draw(this->shopSprite);

    float slotSize = 30.5;

    Text text;
    text.setFont(this->font);
    text.setCharacterSize(8);
    text.setFillColor(sf::Color::White);   

    int xPlacement;
    for(int i = 0; i < this->capacity; i++)
    {
        
        int repartition = i%6;
        switch (repartition)
        {
        case 0:
            xPlacement = 0;
            break;
        
        case 1:
            xPlacement = 2;
            break;
        
        case 2:
            xPlacement = 3;
            break;
        
        case 3:
            xPlacement = 5;
            break;
        
        case 4:
            xPlacement = 6;
            break;
        
        case 5:
            xPlacement = 8;
            break;
        
        default:
            break;
        }
        if(this->itemArray[i] != nullptr)
        {
        Sprite spriteTmp = this->itemArray[i]->getSprite();
        spriteTmp.setScale(1.7,1.7);
        spriteTmp.setPosition(view.getCenter().x - 146 + xPlacement*slotSize,view.getCenter().y - 75 + (i/6)*slotSize);
        window.draw(spriteTmp);

        if(this->itemArray[i]->isStackable())
        {
            text.setString(to_string(this->itemArray[i]->getAmount()));
            text.setPosition(view.getCenter().x - 124 + xPlacement*slotSize,view.getCenter().y - 55 + (i/6)*slotSize);
            window.draw(text);
        }        

        // POur visualiser les rectangles :
        // float slotPosX = view.getCenter().x - 148 + xPlacement * slotSize;
        // float slotPosY = view.getCenter().y - 76 - (i / 6) * slotSize ;        
        // RectangleShape slotRect(Vector2f(slotSize, slotSize));
        // slotRect.setPosition(slotPosX, slotPosY);
        // slotRect.setFillColor(Color::Transparent);
        // slotRect.setOutlineColor(Color::Red);
        // slotRect.setOutlineThickness(1);
        // window.draw(slotRect);
        }        
    }
}

void SellerInventory::drawArrow(RenderWindow &window, View &view, float currentTime)
{
    float slotSize = 30.8;
    for(int i = 0; i < this->capacity/2; i++)
    {
        int xPlacement;      
        int repartition = i%3;
        switch (repartition)
        {
        case 0:
            xPlacement = 1;
            break;
        
        case 1:
            xPlacement = 4;
            break;
        
        case 2:
            xPlacement = 7;
            break;
        
        default:
            break;
        }
        this->arrowArray[i]->setTilePosition(Vector2f(view.getCenter().x - 148 + xPlacement*slotSize,view.getCenter().y - 72 + (i/3)*slotSize));  
        this->arrowArray[i]->drawArrow(window, currentTime);
    }
}

int SellerInventory::handleClick(RenderWindow &window, View &view, Input &input)
{
    if(input.leftClickState())
    {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window), view);

        float slotSize = 30.5;
        int xPlacement;

        for(int i = 0; i < this->capacity; i++)
        {
            int repartition = i%6;
            switch (repartition)
            {
            case 0:
                xPlacement = 0;
                break;
            
            case 1:
                xPlacement = 2;
                break;
            
            case 2:
                xPlacement = 3;
                break;
            
            case 3:
                xPlacement = 5;
                break;
            
            case 4:
                xPlacement = 6;
                break;
            
            case 5:
                xPlacement = 8;
                break;
            
            default:
                break;
            }
            if(this->itemArray[i] != nullptr)
            {
                float slotPosX = view.getCenter().x - 148 + xPlacement * slotSize;
                float slotPosY = view.getCenter().y - 76 + (i / 6) * slotSize ;

                FloatRect slotRect(slotPosX, slotPosY, slotSize, slotSize);

                if(slotRect.contains(mousePos)) 
                {
                    return i;
                    break;
                }
            }        
        }
    }
    return NULL_INT;
}

void SellerInventory::initialize()
{
    this->nbOfItems = 0;
    this->itemArray = new Item*[this->capacity];
    this->arrowArray = new Arrow*[this->capacity/2];
    this->initArrows();
    this->nullify();
}

void SellerInventory::loadTextures()
{
    if(!this->shopTexture.loadFromFile("graphics/shopInventoryText.png"))
        cout << "Erreur lors du chargement de la texture de l'inventaire" << endl;
    else
    {
        this->shopSprite.setTexture(shopTexture);
        this->shopSprite.setScale(1.7,1.7);
    }
}

void SellerInventory::initArrows()
{
    for(int i = 0; i < this->capacity/2; i++)
    {
        arrowArray[i] = new Arrow();
    }    
}
