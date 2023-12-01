#include "player.h"


//Constructeur

Player::Player()
{
	this->loadTexture();
	this->miningClock.restart();
	this->initVariables();

	this->inventory = new PlayerInventory(36);
	this->initStuff();
}

Player::~Player()
{
	delete this->inventory;
}

Vector2i Player::getPlayerPosition(void)
{
    return Vector2i(this->x,this->y);
}

int Player::getGoldAmount(void)
{
    return this->gold;
}

void Player::setGoldAmout(int amout)
{
	this->gold = amout;
}

void Player::addGold(int amout)
{
	this->gold += amout;
}

void Player::removeGold(int amout)
{
	this->gold -= amout;
}

//Fonctions


void Player::drawPlayer(RenderWindow &window)
{
	//Gestion du timer
	if (this->frameTimer <= 0)
	{
		//Animation du personnage
		this->frameTimer = this->TIME_BETWEEN_2_FRAMES_PLAYER;
		this->frameNumber++;
		if (this->frameNumber >= this->frameMax)
			this->frameNumber = 0;

	}
	else
		this->frameTimer--;

	this->farmer.setPosition(Vector2f(this->x, this->y));

	//Gestion de l'orientation du personnage
	if (this->direction == LEFT)
	{
		this->farmer.setTextureRect(sf::IntRect((this->frameNumber + 1) * this->w,this->direction * this->h,-this->w, this->h));
		window.draw(this->farmer);
	}
	else
	{
		this->farmer.setTextureRect(sf::IntRect(this->frameNumber * this->w,this->direction * this->h,this->w, this->h));
		window.draw(this->farmer);
	}
}


void Player::updatePlayer(Input &input, Calque &calqueDeco, Calque &calqueSol, Calque &calquePlants, RenderWindow &window)
{
	if (input.getButton().left == 1)
	{
		if (this->x - PLAYER_SPEED >= 496)
		{
		this->x -= PLAYER_SPEED;
		this->direction = WALK_LEFT;
		}
	}
	else if (input.getButton().right == 1)
	{
		if (this->x + PLAYER_SPEED <= 1376)
		{
			this->x += PLAYER_SPEED;
			this->direction = WALK_RIGHT;
		}
	}
	else if (input.getButton().up == 1)
	{
        if (this->y - PLAYER_SPEED >= 272)
        {
            this->y -= PLAYER_SPEED;
            this->direction = WALK_UP;
        }
	}
	else if (input.getButton().down == 1)
	{
        if (this->y + PLAYER_SPEED <= 1152)
        {
            this->y += PLAYER_SPEED;
            this->direction = WALK_DOWN;
        }
	}
	if (input.getButton().leftClick == 1)
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
		
		int indiceX = worldPosition.x/16;
		int indiceY = worldPosition.y/16;

		this->inventory->updateSelectedItem(input);
		if(this->checkTile(calquePlants, window))
		{
			if(calquePlants.tuiles[indiceY][indiceX]->isMature())
			{
				this->recoltPlant(calquePlants, window, calquePlants.tuiles[indiceY][indiceX]->getValeur());
				return;
			}
		}
		
		switch (this->inventory->getSelectedItem())
		{
		case PICKAXE:
			if(this->checkTile(calqueDeco, window))
				this->destroyTile(calqueDeco, window, PICKAXE);
			break;
		case AXE:
			if(this->checkTile(calqueDeco, window))
				this->destroyTile(calqueDeco, window, AXE);
			break;
		case SICKLE:
			if(this->checkTile(calqueDeco, window))
				this->destroyTile(calqueDeco, window, SICKLE);
			break;
		case HOE:
			if(this->checkTile(calqueSol, window) && !this->checkTile(calqueDeco, window))
				this->destroyTile(calqueSol, window, HOE);
			break;
		case BEETROOT_SEED:
			if(this->checkTile(calqueSol, window) && !this->checkTile(calqueDeco, window))
				this->plant(calqueSol, calquePlants, window, BEETROOT_SEED);
			break;
		case POTATOE_SEED:
			if(this->checkTile(calqueSol, window) && !this->checkTile(calqueDeco, window))
				this->plant(calqueSol, calquePlants, window, POTATOE_SEED);
			break;
		
		default:
			break;
		}
	}
	else
	{
		this->miningClock.restart();
		this->breaking.restartClock(MINING_DURATION);
		this->breaking.setInvisible(window);
	}
}

void Player::initStuff()
{
	this->inventory->add(new Item(PICKAXE));
	this->inventory->add(new Item(AXE));
	this->inventory->add(new Item(HOE));
	this->inventory->add(new Item(SICKLE));
}

bool Player::checkShop(RenderWindow &window, Input &input, FloatRect shopRect, Vector2f sellerPosition)
{
	if (input.getButton().leftClick == 1)
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
		float dist = Utilitaire::distanceCarrei(Vector2i(worldPosition)/16,this->getPlayerPosition()/16);
		
		if (shopRect.contains(worldPosition) && dist < 15)
			return true;
			
	}
	return false;
}

bool Player::checkTile(Calque &calque, RenderWindow &window)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
	
	int indiceX = worldPosition.x/16;
	int indiceY = worldPosition.y/16;

	if(calque.tuiles[indiceY][indiceX] == nullptr)
		return false;
	return true;
}

void Player::destroyTile(Calque &calque, RenderWindow &window, int tool)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
	float dist = Utilitaire::distanceCarrei(Vector2i(worldPosition)/16,this->getPlayerPosition()/16);
	
	int indiceX = worldPosition.x/16;
	int indiceY = worldPosition.y/16;
	int posX = indiceX*16;
	int posY = indiceY*16;

	int value = calque.tuiles[indiceY][indiceX]->getValeur();
	switch (tool)
	{
	/*********************/
	/***    PIOCHE     ***/
	/*********************/

	case PICKAXE:
		if(this->mouseNotChanged && dist < 9 && value == 47)
		{
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				delete calque.tuiles[indiceY][indiceX];
				calque.tuiles[indiceY][indiceX] = nullptr;

				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;
				
				if(!inventory->recolt(STONE))
				{
					// rajouter un système de drop
				}

			}
		}
		else if(dist < 9 && value == 47)
		{
			this->mouseNotChanged = true;
			this->miningClock.restart();

			this->breaking.setTilePosition(Vector2f(posX,posY));
			this->breaking.setTotalTime(calque.tuiles[indiceY][indiceX]->getMiningDuration());
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				delete calque.tuiles[indiceY][indiceX];
				calque.tuiles[indiceY][indiceX] = nullptr;
				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;

				if(!inventory->recolt(STONE))
				{
					// rajouter un système de drop
				}
			}
		}
		else
		{
			this->mouseNotChanged = false;
			this->miningClock.restart();
			this->breaking.setInvisible(window);
		}
		break;

	/*********************/
	/***    HACHE      ***/
	/*********************/

	case AXE:
		if(this->mouseNotChanged && dist < 9 && value == 31)
		{
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				for (int i=-1; i<2; i++)
				{
					for (int j=0; j<4; j++)
					{
						delete calque.tuiles[indiceY-j][indiceX+i];
						calque.tuiles[indiceY-j][indiceX+i] = nullptr;
					}
				}
				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;

				if(!inventory->recolt(WOOD))
				{
					// rajouter un système de drop
				}
			}
		}
		else if(dist < 9 && value == 31)
		{
			this->mouseNotChanged = true;
			this->miningClock.restart();

			this->breaking.setTilePosition(Vector2f(posX,posY));
			this->breaking.setTotalTime(calque.tuiles[indiceY][indiceX]->getMiningDuration());
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				delete calque.tuiles[indiceY][indiceX];
				calque.tuiles[indiceY][indiceX] = nullptr;
				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;

				if(!inventory->recolt(WOOD))
				{
					// rajouter un système de drop
				}
			}
		}
		else
		{
			this->mouseNotChanged = false;
			this->miningClock.restart();
			this->breaking.setInvisible(window);
		}
		break;

	/*********************/
	/***    HOUE       ***/
	/*********************/

	case HOE:
		if(dist < 9 && value == 12)
		{
			delete calque.tuiles[indiceY][indiceX];
			calque.tuiles[indiceY][indiceX] = new Farmland(Vector2f(posX,posY),141);
		}
		break;
	
	/*********************/
	/***    CERPE      ***/
	/*********************/

	case SICKLE:
		if(this->mouseNotChanged && dist < 9 && (value == 40 || value == 41 || value == 49 || value == 50 || value == 38 || value == 39 || value == 48))
		{
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				switch (value)
				{
				case 40:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY+1][indiceX];
					delete calque.tuiles[indiceY][indiceX+1];
					delete calque.tuiles[indiceY+1][indiceX+1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY+1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX+1] = nullptr;
					calque.tuiles[indiceY+1][indiceX+1] = nullptr;
					break;
				case 41:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY+1][indiceX];
					delete calque.tuiles[indiceY][indiceX-1];
					delete calque.tuiles[indiceY+1][indiceX-1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY+1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX-1] = nullptr;
					calque.tuiles[indiceY+1][indiceX-1] = nullptr;	
					break;
				case 49:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY-1][indiceX];
					delete calque.tuiles[indiceY][indiceX+1];
					delete calque.tuiles[indiceY-1][indiceX+1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY-1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX+1] = nullptr;
					calque.tuiles[indiceY-1][indiceX+1] = nullptr;
					break;
				case 50:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY-1][indiceX];
					delete calque.tuiles[indiceY][indiceX-1];
					delete calque.tuiles[indiceY-1][indiceX-1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY-1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX-1] = nullptr;
					calque.tuiles[indiceY-1][indiceX-1] = nullptr;	
					break;
				case 38:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;
				case 39:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;
				case 48:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;
					
				default:
					break;
				}
				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;

				if(!inventory->recolt(WHEAT))
				{
					// rajouter un système de drop
				}
			}
		}
		else if(dist < 9 && (value == 40 || value == 41 || value == 49 || value == 50 || value == 38 || value == 39 || value == 48))
		{
			this->mouseNotChanged = true;
			this->miningClock.restart();

			this->breaking.setTilePosition(Vector2f(posX,posY));
			this->breaking.setTotalTime(calque.tuiles[indiceY][indiceX]->getMiningDuration());
			this->breaking.drawBreaking(window,this->miningClock);

			if(this->miningClock.getElapsedTime().asMilliseconds() >= calque.tuiles[indiceY][indiceX]->getMiningDuration())
			{
				switch (value)
				{
				case 40:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY+1][indiceX];
					delete calque.tuiles[indiceY][indiceX+1];
					delete calque.tuiles[indiceY+1][indiceX+1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY+1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX+1] = nullptr;
					calque.tuiles[indiceY+1][indiceX+1] = nullptr;
					break;
				case 41:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY+1][indiceX];
					delete calque.tuiles[indiceY][indiceX-1];
					delete calque.tuiles[indiceY+1][indiceX-1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY+1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX-1] = nullptr;
					calque.tuiles[indiceY+1][indiceX-1] = nullptr;	
					break;
				case 49:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY-1][indiceX];
					delete calque.tuiles[indiceY][indiceX+1];
					delete calque.tuiles[indiceY-1][indiceX+1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY-1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX+1] = nullptr;
					calque.tuiles[indiceY-1][indiceX+1] = nullptr;
					break;
				case 50:
					delete calque.tuiles[indiceY][indiceX];
					delete calque.tuiles[indiceY-1][indiceX];
					delete calque.tuiles[indiceY][indiceX-1];
					delete calque.tuiles[indiceY-1][indiceX-1];
					calque.tuiles[indiceY][indiceX] = nullptr;
					calque.tuiles[indiceY-1][indiceX] = nullptr;
					calque.tuiles[indiceY][indiceX-1] = nullptr;
					calque.tuiles[indiceY-1][indiceX-1] = nullptr;	
					break;
				case 38:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;
				case 39:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;
				case 48:
					delete calque.tuiles[indiceY][indiceX];
					calque.tuiles[indiceY][indiceX] = nullptr;
					break;

				default:
					break;
				}
				this->miningClock.restart();
				this->breaking.setInvisible(window);
				this->mouseNotChanged = false;

				if(!inventory->recolt(WHEAT))
				{
					// rajouter un système de drop
				}			
			}
		}
		else
		{
			this->mouseNotChanged = false;
			this->miningClock.restart();
			this->breaking.setInvisible(window);
		}
		break;


	default:
		break;
	}
}

void Player::plant(Calque &calqueSol, Calque &calquePlants, RenderWindow &window, int seedType)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
	
	int indiceX = worldPosition.x/16;
	int indiceY = worldPosition.y/16;

	if(calqueSol.tuiles[indiceY][indiceX]->getValeur() == 141 && !this->checkTile(calquePlants, window))
	{
		calquePlants.tuiles[indiceY][indiceX] = new Plant(Vector2f(indiceX*16,indiceY*16),seedType);
		int seedIndex = this->inventory->findItem(seedType);
		this->inventory->updateItem(seedIndex, -1);
	}
}

void Player::recoltPlant(Calque &calquePlants, RenderWindow &window, int plantType)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
	float dist = Utilitaire::distanceCarrei(Vector2i(worldPosition)/16,this->getPlayerPosition()/16);
	
	int indiceX = worldPosition.x/16;
	int indiceY = worldPosition.y/16;

	switch (plantType)
	{
	case BEETROOT_SEED:
		if(dist < 9)
		{
			delete calquePlants.tuiles[indiceY][indiceX];
			calquePlants.tuiles[indiceY][indiceX] = nullptr;
			
			if(!inventory->recolt(BEETROOT))
			{
				// rajouter un système de drop
			}
		}
		break;
	case POTATOE_SEED:
		if(dist < 9)
		{
			delete calquePlants.tuiles[indiceY][indiceX];
			calquePlants.tuiles[indiceY][indiceX] = nullptr;
			
			if(!inventory->recolt(POTATOE))
			{
				// rajouter un système de drop
			}
		}
		break;
	default:
		break;
	}
}

void Player::buy(int index, SellerInventory &sellerInventory, float currentTime)
{
	if(currentTime - this->lastBuyTime < SHOP_COOLDOWN)
		return;
	
	this->lastBuyTime = currentTime;

	if(index % 2 == 1)
		index--; //Dans la logique de mon shop l'item en position paire est l'item à vendre et celui en position impair est celui que le joueur achète
	
	int buyType = sellerInventory.getItemType(index);
	int buyAmount = sellerInventory.getItemAmount(index);
	
	int sellType = sellerInventory.getItemType(index+1);
	int sellAmount = sellerInventory.getItemAmount(index+1);

	if(this->inventory->containAmount(buyType, buyAmount))
	{
		int buyIndex = this->inventory->findItem(buyType);
		this->inventory->updateItem(buyIndex, -buyAmount);

		if(this->inventory->contain(sellType))
		{
			int sellIndex = this->inventory->findItem(sellType);
			this->inventory->updateItem(sellIndex, sellAmount);
		}
		else
		{
			this->inventory->add(new Item(sellType, sellAmount));
		}
	} 
	else
	{
		// to do
	}

}

void Player::loadTexture()
{
	//Chargement du spritesheet
	if (!this->farmerTexture.loadFromFile("graphics/farmer.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement du spritesheet." << endl;
	}
	else
		this->farmer.setTexture(this->farmerTexture);
}

void Player::initVariables()
{
	this->frameNumber = 0;	//Indique le numéro de la frame où commencer
	this->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	this->frameMax = 3;	//Dépend du nombre de frame que contient le skin

	this->gold = 0;
	this->lastBuyTime = 0;

	this->x = 928;
	this->y = 720;

	this->direction = WALK_DOWN;

	this->w = PLAYER_WIDTH;
	this->h = PLAYER_HEIGTH;

	this->mouseNotChanged = false;
}
