#include "playerInventory.h"

PlayerInventory::PlayerInventory(int capacity) : Inventory(capacity)
{
    this->initialize();
    this->loadTextures();
}

PlayerInventory::~PlayerInventory()
{
}

int PlayerInventory::getSelectedItem()
{
	return this->selectedItem;
}

int PlayerInventory::getSelectedNum(Input &input)
{
    return input.getSelectedNum();
}

void PlayerInventory::updateSelectedItem(Input &input)
{
    this->selectedItem = this->getItemType(input.getSelectedNum());
}

bool PlayerInventory::recolt(const int itemType)
{
    switch (itemType)
    {
    case STONE:
        for (int i = 0; i < this->capacity; ++i)
        {
            if (this->itemArray[i] != nullptr)
            {
                if (this->itemArray[i]->getType() == STONE)
                {
                    this->itemArray[i]->updateAmount(1);
                    return true;
                }                
            }
        }

        if (this->nbOfItems < this->capacity) {
            Item* stoneItem = new Item(STONE);
            this->add(stoneItem);
            return true;
        }

        return false;
        break;

    case WOOD:
        for (int i = 0; i < this->capacity; ++i)
        {
            if (this->itemArray[i] != nullptr)
            {
                if (this->itemArray[i]->getType() == WOOD)
                {
                    this->itemArray[i]->setAmount(this->itemArray[i]->getAmount() + 1);
                    return true;
                }                
            }
        }

        if (this->nbOfItems < this->capacity) {
            Item* woodItem = new Item(WOOD,2);
            this->add(woodItem);
            return true;
        }

        return false;
        break;

    case WHEAT:
        for (int i = 0; i < this->capacity; ++i)
        {
            if (this->itemArray[i] != nullptr)
            {
                if (this->itemArray[i]->getType() == WHEAT)
                {
                    this->itemArray[i]->setAmount(this->itemArray[i]->getAmount() + 1);
                    return true;
                }                
            }
        }

        if (this->nbOfItems < this->capacity) {
            Item* wheatItem = new Item(WHEAT);
            this->add(wheatItem);
            return true;
        }
        return false;
        break;

    case BEETROOT:
        for (int i = 0; i < this->capacity; ++i)
        {
            if (this->itemArray[i] != nullptr)
            {
                if (this->itemArray[i]->getType() == BEETROOT)
                {
                    this->itemArray[i]->setAmount(this->itemArray[i]->getAmount() + 1);
                    return true;
                }                
            }
        }

        if (this->nbOfItems < this->capacity) {
            Item* potatoeItem = new Item(BEETROOT);
            this->add(potatoeItem);
            return true;
        }
        return false;
        break;

    case POTATOE:
        for (int i = 0; i < this->capacity; ++i)
        {
            if (this->itemArray[i] != nullptr)
            {
                if (this->itemArray[i]->getType() == POTATOE)
                {
                    this->itemArray[i]->setAmount(this->itemArray[i]->getAmount() + 1);
                    return true;
                }                
            }
        }

        if (this->nbOfItems < this->capacity) {
            Item* potatoeItem = new Item(POTATOE);
            this->add(potatoeItem);
            return true;
        }
        return false;
        break;
    
    default:
        return false;
        break;
    }
}

void PlayerInventory::drawInventory(RenderWindow &window, View &view)
{
    this->inventorySprite.setPosition(view.getCenter().x - 255, view.getCenter().y - 124);
    window.draw(this->inventorySprite);
    int slotSize = 54;

    Text text;
    text.setFont(this->font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);   

    for(int i = 0; i < 9; i++)
    {
        if(this->itemArray[i] != nullptr)
        {
        Sprite spriteTmp = this->itemArray[i]->getSprite();
        spriteTmp.setScale(3,3);
        spriteTmp.setPosition(view.getCenter().x - 230 + i*slotSize,view.getCenter().y + 74);
        window.draw(spriteTmp);

        if(this->itemArray[i]->isStackable())
        {
            text.setString(to_string(this->itemArray[i]->getAmount()));
            text.setPosition(view.getCenter().x - 230+38 + i*slotSize,view.getCenter().y + 108);
            window.draw(text);
        }        

        // Pour visualiser les cases
        // float slotPosX = view.getCenter().x - 230 + (i % 9) * slotSize;
        // float slotPosY = view.getCenter().y + 74;        
        // RectangleShape slotRect(Vector2f(slotSize, slotSize));
        // slotRect.setPosition(slotPosX, slotPosY);
        // slotRect.setFillColor(Color::Transparent);
        // slotRect.setOutlineColor(Color::Red);
        // slotRect.setOutlineThickness(1);      
        // window.draw(slotRect);

        }
    }
    for(int i = 9; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr)
        {
        Sprite spriteTmp = this->itemArray[i]->getSprite();
        spriteTmp.setScale(3,3);
        spriteTmp.setPosition(view.getCenter().x - 230 + (i%9)*slotSize,view.getCenter().y + 60 - (i/9)*slotSize);
        window.draw(spriteTmp);

        if(this->itemArray[i]->isStackable())
        {
            text.setString(to_string(this->itemArray[i]->getAmount()));
            text.setPosition(view.getCenter().x - 192 + (i%9)*slotSize,view.getCenter().y + 94 - (i/9)*slotSize);
            window.draw(text);
        }

        // Pour visualiser les cases
        // float slotPosX = view.getCenter().x - 230 + (i % 9) * slotSize;
        // float slotPosY = view.getCenter().y + 60 - (i / 9) * slotSize ;
        // RectangleShape slotRect(Vector2f(slotSize, slotSize));
        // slotRect.setPosition(slotPosX, slotPosY);
        // slotRect.setFillColor(Color::Transparent);
        // slotRect.setOutlineColor(Color::Red);
        // slotRect.setOutlineThickness(1);
        // window.draw(slotRect);
        }
    }
}

void PlayerInventory::drawInShopInventory(RenderWindow &window ,View &view)
{
    float slotSize = 30.5;

    Text text;
    text.setFont(this->font);
    text.setCharacterSize(8);
    text.setFillColor(sf::Color::White);   

    for(int i = 0; i < 9; i++)
    {
        if(this->itemArray[i] != nullptr)
        {
        Sprite spriteTmp = this->itemArray[i]->getSprite();
        spriteTmp.setScale(1.7,1.7);
        spriteTmp.setPosition(view.getCenter().x - 146 + i*slotSize,view.getCenter().y + 232);
        window.draw(spriteTmp);

        if(this->itemArray[i]->isStackable())
        {
            text.setString(to_string(this->itemArray[i]->getAmount()));
            text.setPosition(view.getCenter().x - 124+ i*slotSize,view.getCenter().y + 250);
            window.draw(text);
        }        

        // float slotPosX = view.getCenter().x - 148 + (i % 9) * slotSize;
        // float slotPosY = view.getCenter().y + 230;
        // RectangleShape slotRect(Vector2f(slotSize, slotSize));
        // slotRect.setPosition(slotPosX, slotPosY);
        // slotRect.setFillColor(Color::Transparent);
        // slotRect.setOutlineColor(Color::Red);
        // slotRect.setOutlineThickness(1);
        // window.draw(slotRect);
        }
    }
    for(int i = 9; i < this->capacity; i++)
    {
        if(this->itemArray[i] != nullptr)
        {
        Sprite spriteTmp = this->itemArray[i]->getSprite();
        spriteTmp.setScale(1.7,1.7);
        spriteTmp.setPosition(view.getCenter().x - 146 + (i%9)*slotSize,view.getCenter().y + 224 - (i/9)*slotSize);
        window.draw(spriteTmp);

        if(this->itemArray[i]->isStackable())
        {
            text.setString(to_string(this->itemArray[i]->getAmount()));
            text.setPosition(view.getCenter().x - 124 + (i%9)*slotSize,view.getCenter().y + 244 - (i/9)*slotSize);
            window.draw(text);
        }

        // float slotPosX = view.getCenter().x - 148 + (i % 9) * slotSize;
        // float slotPosY = view.getCenter().y + 222 - (i / 9) * slotSize ;
        // RectangleShape slotRect(Vector2f(slotSize, slotSize));
        // slotRect.setPosition(slotPosX, slotPosY);
        // slotRect.setFillColor(Color::Transparent);
        // slotRect.setOutlineColor(Color::Red);
        // slotRect.setOutlineThickness(1);
        // window.draw(slotRect);
        }
    }
}

void PlayerInventory::drawHotbar(RenderWindow &window, View &view, Input& input)
{
    this->hotbarSprite.setPosition(view.getCenter().x - 160, view.getCenter().y + 220);
    window.draw(this->hotbarSprite);

    Text text;
    text.setFont(this->font);
    text.setCharacterSize(11);
    text.setFillColor(sf::Color::White);

    if(this->capacity < 8)
    {
        for(int i = 0; i < this->capacity; i++)
        {
            if(this->itemArray[i] != nullptr)
            {            
                Sprite spriteTmp = this->itemArray[i]->getSprite();
                spriteTmp.setScale(2,2);
                spriteTmp.setPosition(view.getCenter().x - 153 + i*36,view.getCenter().y + 227);
                window.draw(spriteTmp);
                if(this->itemArray[i]->isStackable())
                {
                    text.setString(to_string(this->itemArray[i]->getAmount()));
                    text.setPosition(view.getCenter().x - 128 + i*36,view.getCenter().y + 246);
                    window.draw(text);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < 9; i++)
        {
            if(this->itemArray[i] != nullptr)
            {            
                Sprite spriteTmp = this->itemArray[i]->getSprite();
                spriteTmp.setScale(2,2);
                spriteTmp.setPosition(view.getCenter().x - 153 + i*36,view.getCenter().y + 227);
                window.draw(spriteTmp);
                if(this->itemArray[i]->isStackable())
                {
                    text.setString(to_string(this->itemArray[i]->getAmount()));
                    text.setPosition(view.getCenter().x - 128 + i*36,view.getCenter().y + 246);
                    window.draw(text);
                }
            }
        }
    }
    this->hightlightSprite.setPosition(view.getCenter().x - 156 + 36*this->getSelectedNum(input), view.getCenter().y + 224);
    window.draw(this->hightlightSprite);
}

void PlayerInventory::handleClick(RenderWindow &window, View &view, Input &input) {
    if(input.leftClickState())
    {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window), view);

        float slotSize = 54;

        for(int i = 0; i < 9; i++)
        {
            if(this->itemArray[i] != nullptr)
            {

                float slotPosX = view.getCenter().x - 230 + (i % 9) * slotSize;
                float slotPosY = view.getCenter().y + 74;
                FloatRect slotRect2(slotPosX, slotPosY, slotSize, slotSize);

                // Pour visualiser les rectangles                
                // RectangleShape slotRect(Vector2f(slotSize, slotSize));
                // slotRect.setPosition(slotPosX, slotPosY);
                // slotRect.setFillColor(Color::Transparent);
                // slotRect.setOutlineColor(Color::Red);
                // slotRect.setOutlineThickness(1);
                // window.draw(slotRect);

                if(slotRect2.contains(mousePos)) 
                {
                    // // handleItemSelection(i);
                    // cout << i << endl;
                    break;
                }
            }
        }

        for(int i = 9; i < this->capacity; i++)
        {
            if(this->itemArray[i] != nullptr)
            {
                float slotPosX = view.getCenter().x - 230 + (i % 9) * slotSize;
                float slotPosY = view.getCenter().y + 60 - (i / 9) * slotSize ;

                RectangleShape slotRect(Vector2f(slotSize, slotSize));
                slotRect.setPosition(slotPosX, slotPosY);
                slotRect.setFillColor(Color::Transparent);
                slotRect.setOutlineColor(Color::Red);
                slotRect.setOutlineThickness(1);

                window.draw(slotRect);

                FloatRect slotRect2(slotPosX, slotPosY, slotSize, slotSize);

                if(slotRect2.contains(mousePos)) 
                {
                    // // handleItemSelection(i);
                    // cout << i << endl;
                    break;
                }
            }        
        }
    }
}

void PlayerInventory::initialize()
{
    this->nbOfItems = 0;
    this->selectedItem = PICKAXE;
    this->itemArray = new Item*[this->capacity];

    this->nullify();
}

void PlayerInventory::loadTextures()
{
    if(!this->inventoryTexture.loadFromFile("graphics/inventaire.png"))
        cout << "Erreur lors du chargement de la texture de l'inventaire" << endl;
    else
    {
        this->inventorySprite.setTexture(inventoryTexture);
        this->inventorySprite.setScale(3,3);
    }

    if(!this->hotbarTexture.loadFromFile("graphics/hotbar.png"))
        cout << "Erreur lors du chargement de la texture de la hotbar" << endl;
    else
    {
        this->hotbarSprite.setTexture(hotbarTexture);
        this->hotbarSprite.setScale(2,2);
    }
    if(!this->hightlightTexture.loadFromFile("graphics/hightlight.png"))
        cout << "Erreur lors du chargement de la texture de l'higtlight" << endl;
    else
    {
        this->hightlightSprite.setTexture(hightlightTexture);
        this->hightlightSprite.setScale(2,2);
    }
}