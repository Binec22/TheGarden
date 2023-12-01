#include "game.h"

Game::Game() : window(VideoMode(1920, 1440, 16), "The Garden"), calque1(1), calque2(2), calque3(3), calque4(4)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    view = View(sf::FloatRect(0, 0, 960, 560));
}

void Game::run()
{
    while (window.isOpen())
    {
		float currentTime = gameClock.getElapsedTime().asMilliseconds();;
		input.gestionInputs(window);
		Vector2i pos = player.getPlayerPosition();
		view.setCenter(pos.x,pos.y);
		window.setView(view);
        window.clear();

		calque1.setUpTiles(window, view);
		calque2.setUpTiles(window, view);
		calque3.setUpTiles(window, view);
		calque4.drawPlants(window, view, currentTime);
        arrow.drawArrow(window, currentTime);
        seller.drawSeller(window);
        player.drawPlayer(window);

		if(input.getInventoryToggle())
		{
			player.inventory->drawInventory(window,view);
			player.inventory->handleClick(window, view, input);
			window.display();

			continue;
		}

		if(input.isShopOpen())
		{		
			seller.sellerInventory->drawSellerInventory(window,view);
			player.inventory->drawInShopInventory(window,view);
			seller.sellerInventory->drawArrow(window,view,currentTime);
			int index = seller.sellerInventory->handleClick(window, view, input);
			if (index != NULL_INT)
				player.buy(index, *seller.sellerInventory, currentTime);
			window.display();

			continue;
		}

		player.updatePlayer(input, calque3, calque1, calque4, window);
		
		if(player.checkShop(window, input, seller.sellerSprite.getGlobalBounds(), seller.sellerSprite.getPosition()))
			input.switchShopState(true);

		player.inventory->drawHotbar(window, view, input);
		

		window.display();
    }
}