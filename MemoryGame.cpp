#include "main.h"



int main()
{
	Main::window.setKeyRepeatEnabled(false);
	Main::window.setFramerateLimit(60);

	unsigned int seconds = 0;

	Menu menu;
	menu.initialize();

	Card* pCard = nullptr;

	Deck deck;
	deck.display();
	deck.shuffleCards();
	deck.initialize();

	Player player;
	player.initialize();

	sf::Time delta;
	sf::Clock clock;

	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mouseScreenPosition;

	enum class GameState
	{
		INTRO,
		PLAYER_INPUT,
		PLAYING,
		END
	};
	GameState gameState = GameState::INTRO;

	SoundManager::getInstance()->playMusic(Filename::musicFilename);

	while (Main::window.isOpen())
	{
		Main::window.clear();

		/********** DRAW **********/
		switch (gameState)
		{
		case GameState::INTRO:
			menu.draw();
			menu.drawIntro();
			break;
		case GameState::PLAYER_INPUT:
			menu.draw();
			player.draw();
			menu.drawInput();
			break;
		case GameState::PLAYING:
			menu.draw();
			deck.drawDeck();
			player.drawHud();
			break;
		case GameState::END:
			menu.draw();
			menu.drawEnd();
			player.drawResult();
			break;
		}

		Main::window.display();

		sf::Event Event;
		while (Main::window.pollEvent(Event))
		{
			if ((Event.type == sf::Event::Closed) || (Event.type == sf::Event::KeyPressed)
				&& (Event.key.code == sf::Keyboard::Escape))
			{
				Main::window.close();
			}
			if ((Event.type == sf::Event::MouseButtonReleased))
			{
				pCard && gameState != GameState::END ? SoundManager::getInstance()->playSound(Resource::Sound, Filename::cardFlip)
					: SoundManager::getInstance()->playSound(Resource::Sound, Filename::clickSound);
			}
			if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
			{
				mouseScreenPosition = sf::Mouse::getPosition();
				mouseWorldPosition = Main::window.mapPixelToCoords(sf::Mouse::getPosition());
				menu.musicSwitch();

				switch (gameState)
				{
				case GameState::INTRO:
					if (menu.textClick())
					{
						if (menu.quitRect())
						{
							Main::window.close();
						}
						else {
							gameState = GameState::PLAYER_INPUT;
						}
					}
					break;
				case GameState::PLAYER_INPUT:
					if (menu.textClick())
					{
						gameState = GameState::PLAYING;
					}
					break;
				case GameState::PLAYING: 
					pCard = deck.clickCard(mouseWorldPosition);
					if (pCard)
					{
						if (deck.pickCards(pCard, player, delta))
						{
							deck.matched(player);
							if (player.allMatching()) {
								sf::sleep(sf::milliseconds(50));
								gameState = GameState::END;
							}
						}
						else if (deck.unmatched()) {
							deck.clearChoices();
							deck.pickCards(pCard, player, delta);
						}
					}
					break;
				case GameState::END:
					if (menu.textClick())
					{
						if (menu.quitRect())
						{
							Main::window.close();
						}
						else {
							gameState = GameState::PLAYER_INPUT;
							player.clearPlayerInput();
							player.resetScore();
							deck.clearChoices();
						}
					}
					break;
				}
			} // End of mouse type event

			if (Event.type == sf::Event::TextEntered)
			{
				if (gameState == GameState::PLAYER_INPUT)
				{
					player.playerInput(Event);
				}
			}
		} // End of Event

		  /********** UPDATE **********/
		menu.update();
		seconds = static_cast<unsigned>(delta.asSeconds());

		switch (gameState)
		{
		case GameState::PLAYER_INPUT:
			delta = clock.restart();
			break;
		case GameState::PLAYING:
			delta = clock.getElapsedTime();
			deck.update(mouseWorldPosition);
			player.update(delta, seconds);
			if (pCard != nullptr) 
			{
				pCard->update(delta); 
			}
			break;
		case GameState::END:
			SoundManager::getInstance()->stopMusic();
			player.rating();
			player.update(delta, seconds);
			deck.resetCards();
			clock.restart();
			if (menu.textClick())
			{
				// Play music when the game is repeated
				SoundManager::getInstance()->playMusic(Filename::musicFilename);
			}
			break;
		}
		if (gameState != GameState::PLAYING)
			continue;

	} // End of while loop

	return 0;
}



