#include <iostream>

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

#include "Textbox.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	std::unique_ptr<sf::RenderWindow> upWnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280U, 720U, 32U), "Template", sf::Style::Close, settings);


	upWnd->setKeyRepeatEnabled(true);
	sf::Font aFont;
	aFont.loadFromFile("fonts/afont2.ttf");
	TextBox textbox1(30U, sf::Color::White, true, aFont, {65.f, 220.f}, { 300, 100 });
	// textbox1.typedOn(e);
	// textbox1.drawTo(*upWnd);
	
	while (upWnd->isOpen())
	{
		sf::Event e;
		while (upWnd->pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					upWnd->close();
					break;
				case sf::Event::KeyPressed:
					if (e.key.code == sf::Keyboard::Escape)
					{
						upWnd->close();
					}
					break;
				case sf::Event::TextEntered:
					textbox1.typedOn(e);
					break;
				default:
					break;
			}

		}
		upWnd->clear(sf::Color(47, 147, 247, 255));
		textbox1.drawTo(*upWnd);
		upWnd->display();
	}

	return EXIT_SUCCESS;
}