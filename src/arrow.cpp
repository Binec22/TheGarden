#include "arrow.h"

Arrow::Arrow()
{
    //Chargement du spritesheet
	if (!this->arrowTexture.loadFromFile("graphics/arrow.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de la flèche." << endl;
	}
	else
		this->arrowSprite.setTexture(arrowTexture);
    
    this->row = 0;
    this->line = 0;
    this->frameNumber = 0;
    this->frameMax = 20;
    this->frameTimer = 0.0f;
    this->lastFrameTime = 0.0f;
	this->timeBetween2Frames = 50.0f;
}

void Arrow::setTilePosition(Vector2f newPosition)
{
    this->arrowSprite.setPosition(newPosition);
}

void Arrow::drawArrow(RenderWindow &window, float currentTime)
{
	if (currentTime - this->lastFrameTime > this->timeBetween2Frames)
	{
        this->lastFrameTime = currentTime;
		this->frameNumber++;
		if (this->frameNumber >= this->frameMax)
			this->frameNumber = 0;
	}
    this->arrowSprite.setTextureRect(sf::IntRect((this->frameNumber%4) * ARROW_WIDTH,(this->frameNumber/4) * ARROW_HEIGHT,ARROW_WIDTH,ARROW_HEIGHT));
    window.draw(this->arrowSprite);
}
