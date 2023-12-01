#include "input.h"

using namespace std;
using namespace sf;

//Constructeur
Input::Input()
{
	button.left = button.right = button.up = button.down = button.inventory = button.leftClick = false;
	selectedNum = NUM_ONE;
	inventoryToggle = false;
	shopOpen = false;
}


//Accesseur
Input::Button Input::getButton(void) const { return button; }

void Input::gestionInputs(RenderWindow &window) { getInput(window);}

bool Input::getInventoryToggle() const 
{
    return inventoryToggle;
}

bool Input::isShopOpen() const
{
    return this->shopOpen;
}

bool Input::leftClickState() const
{
    return this->button.leftClick;
}

int Input::getSelectedNum() const
{
	return selectedNum;
}

//Mutateur
void Input::setButton(int bouton, bool etat)
{
	switch (bouton)
	{
	case up:
		button.up = etat;
		break;

	case down:
		button.down = etat;
		break;

	case right:
		button.right = etat;
		break;

	case left:
		button.left = etat;
		break;

	case leftClick:
		button.leftClick = etat;
		break;
	}
}

void Input::setInventoryToggle(bool etat)
{
    inventoryToggle = etat;
}

void Input::switchShopState(bool etat)
{
	this->shopOpen = etat;
}

void Input::getInput(RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// On ferme la fenêtre
		case Event::Closed:
			window.close();
			break;
		
			// Bouttons de la souris
		case Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case Mouse::Left:
				button.leftClick = true;
				break;
			
			default:
				break;
			}


			// Touche pressée
		case Event::KeyPressed:
			switch (event.key.code) // La touche qui a été pressée
			{
			case Keyboard::Escape: // Echap
				if (this->isShopOpen())
					this->shopOpen = false;
				else if (this->inventoryToggle)
					this->inventoryToggle = false;
				else				
					window.close();
				break;

			case Keyboard::Q:
				button.left = true;
				break;

			case Keyboard::D:
				button.right = true;
				break;

			case Keyboard::S:
				button.down = true;
				break;

			case Keyboard::Z:
				button.up = true;
				break;	

			case Keyboard::E:
				setInventoryToggle(!getInventoryToggle());
				break;

			case Keyboard::Num1:
				selectedNum = NUM_ONE;
				break;

			case Keyboard::Num2:
				selectedNum = NUM_TWO;
				break;

			case Keyboard::Num3:
				selectedNum = NUM_THREE;
				break;

			case Keyboard::R:
				selectedNum = NUM_FOUR;
				break;
			
			case Keyboard::Num5:
				selectedNum = NUM_FIVE;
				break;
			
			case Keyboard::T:
				selectedNum = NUM_SIX;
				break;

			case Keyboard::Num7:
				selectedNum = NUM_SEVEN;
				break;

			case Keyboard::Num8:
				selectedNum = NUM_EIGHT;
				break;

			case Keyboard::Num9:
				selectedNum = NUM_NINE;
				break;
			
			default:
				break;
			}
			break;

			// Touche relâchée
		case Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
			case Mouse::Left:
				button.leftClick = false;
				break;
			
			default:
				break;
			}

		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Q:
				button.left = false;
				break;

			case Keyboard::D:
				button.right = false;
				break;

			case Keyboard::S:
				button.down = false;
				break;

			case Keyboard::Z:
				button.up = false;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}
