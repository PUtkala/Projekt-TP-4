// Projekt TP Patryk Utkała Piotr Żulinski.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
void moveLifter(int &lifterPositionx , int &lifterPositiony);
int main()
{
	int lifterPositionx= 400;
	int lifterPositiony= 50;
	sf::RenderWindow okno(sf::VideoMode(1000, 600), "Dzwig");
	sf::Clock stoper;
	sf::Texture texture;
	if (!texture.loadFromFile("dzwig.jpg"))
	{
		// error...
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno.close();

		} //while
		okno.clear(sf::Color(255, 255, 255));

		sprite.setPosition(250, 75);
		okno.draw(sprite);
		moveLifter(lifterPositionx, lifterPositiony);
		sf::RectangleShape lifter(sf::Vector2f(5, lifterPositiony));
		lifter.setPosition(lifterPositionx, 130);
		lifter.setFillColor(sf::Color(0, 0, 0));
		okno.draw(lifter);

		sf::RectangleShape ground(sf::Vector2f(1000, 5));
		ground.setPosition(0, 450); 
		ground.setFillColor(sf::Color(0, 0, 0));
		okno.draw(ground);
		sf::Text text;
		

		okno.display();
	} //while
	return 0;
}
void moveLifter(int &lifterPositionx, int &lifterPositiony) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && lifterPositionx < 630)
	{
		lifterPositionx += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && lifterPositionx > 400)
	{
		lifterPositionx -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && lifterPositiony < 300)
	{
		lifterPositiony += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && lifterPositiony > 20)
	{
		lifterPositiony -= 1;
	}

}
