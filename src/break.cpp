#include "break.h"

Break::Break()
{
    //Chargement du spritesheet
	if (!this->breakTexture.loadFromFile("graphics/break.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement du spritesheet." << endl;
	}
	else
		this->breakSprite.setTexture(breakTexture);
    
    this->frameNumber = 0;
    this->frameMax = 7;
    this->frameTimer = 0;
	this->timeBetween2Frames = 0;
	this->breakClock.restart();
}

void Break::setTilePosition(Vector2f newPosition)
{
	this->breakSprite.setPosition(newPosition);
}

void Break::setTotalTime(float totalTime)
{
	this->timeBetween2Frames = totalTime/this->frameMax;
}

void Break::drawBreaking(RenderWindow &window, Clock clock)
{
	//Gestion du timer
	if (clock.getElapsedTime().asMilliseconds() >= this->timeBetween2Frames * (this->frameNumber +1))
	{
		this->frameNumber++;
		if (this->frameNumber >= this->frameMax)
			this->frameNumber = 0;
	}
    this->breakSprite.setTextureRect(sf::IntRect(this->frameNumber*TILE_SIZE,0,TILE_SIZE,TILE_SIZE)); // plus qu'à modifier ici et ça devrait être bon !
    window.draw(this->breakSprite);
}

void Break::restartClock(float totalTime)
{
	this->timeBetween2Frames = totalTime/this->frameMax;
	this->frameNumber = 0;
	this->breakClock.restart();
}

void Break::setInvisible(RenderWindow &window)
{
	this->breakSprite.setTextureRect(sf::IntRect(8*TILE_SIZE,0,TILE_SIZE,TILE_SIZE)); 
    window.draw(this->breakSprite);
}
