#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

enum nums{NUM_ONE = 0, NUM_TWO, NUM_THREE, NUM_FOUR, NUM_FIVE, NUM_SIX, NUM_SEVEN, NUM_EIGHT, NUM_NINE};


class Input
{

//Structures
struct Button { bool left, right, up, down, inventory, leftClick, one, two, three, four, five, six, seven, eight, nine;};	

public:
	//Constructeur
	Input();

	//Accesseur
	Button getButton(void) const;
    bool getInventoryToggle() const;
	bool isShopOpen() const;
	bool leftClickState() const;
	int getSelectedNum() const;

	//Mutateur
	void setButton(int bouton, bool etat);
	void setInventoryToggle(bool etat);
	void switchShopState(bool etat);

	//Méthodes
	void gestionInputs(sf::RenderWindow &window);
	void getInput(sf::RenderWindow &window);
	


private:
	sf::Event event;
	Button button;

	bool inventoryToggle;
	bool shopOpen;
	int selectedNum;

	//Enum pour les boutons
	enum { up, down, right, left, leftClick};
};
#endif