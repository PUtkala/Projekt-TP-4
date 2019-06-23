// Projekt TP Patryk Utkała Piotr Żulinski.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const int buttonLenght = 30;
const int buttonHight = 30;

class box {
public:
	int type ;
	int posx ;
	int posy ;
	int size = 50;

	box(int typed, int posxd, int posyd) {
		type = typed;
		posx = posxd;
		posy = posyd;
	}
	void move() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && posx < 630)
		{
			posx += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && posx > 400)
		{
			posx -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && posy < 400)
		{
			posy += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && posy > 20 - size)
		{
			posy -= 1;
		}
	}
	void fall() {
		if(posy< 400)
		posy += 1;
	}
	void collision(std::vector <box> &boxes,int same) {
		for (int i = 0; i < boxes.size(); i++) {
			if (posx > boxes[i].posx - size && posx < boxes[i].posx + size && posy > boxes[i].posy - size && posy < boxes[i].posy + size && same != i) {
				posy -= size + posy - boxes[i].posy;
			}
		}
	}

};

void moveLifter(int &lifterPositionx , int &lifterPositiony);
void drawLifter(sf::RenderWindow &okno, int &lifterPositionx, int &lifterPositiony);
void drawButtons(sf::RenderWindow &okno);
void spawner(sf::RenderWindow &okno, std::vector <box> &boxes, bool &mouseClicked);
void drawBoxes(sf::RenderWindow &okno, std::vector <box> &boxes);
void magnet(int &lifterPositionx, int &lifterPositiony, std::vector <box> &boxes);
int main()
{
	std::vector <box> boxes;
	int lifterPositionx= 400;
	int lifterPositiony= 50;
	bool mouseClicked=0;
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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouseClicked = 1;
				}
			}
		} //while
		
		okno.clear(sf::Color(255,255,255));

		sprite.setPosition(250, 75);
		okno.draw(sprite);

		moveLifter(lifterPositionx, lifterPositiony);
		drawButtons(okno);
		drawLifter(okno, lifterPositionx, lifterPositiony);
		spawner(okno,boxes,mouseClicked);
		drawBoxes(okno,boxes);
		magnet(lifterPositionx, lifterPositiony, boxes);

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
void drawLifter(sf::RenderWindow &okno, int &lifterPositionx, int &lifterPositiony) {
	sf::RectangleShape lifter(sf::Vector2f(5, lifterPositiony));
	lifter.setPosition(lifterPositionx, 130);
	lifter.setFillColor(sf::Color(0, 0, 0));
	okno.draw(lifter);

	sf::RectangleShape magnet(sf::Vector2f(30, 10));
	magnet.setPosition(lifterPositionx - 12.5, 130 + lifterPositiony);
	magnet.setFillColor(sf::Color(0, 0, 0));
	okno.draw(magnet);
}
void drawButtons(sf::RenderWindow &okno) {
	for (int i = 0; i < 3; i++) {
		sf::RectangleShape button(sf::Vector2f(buttonLenght,buttonHight));
		button.setPosition(10,5 + 1.5*i*buttonHight);
		button.setFillColor(sf::Color(200, 0, 0));
		button.setOutlineThickness(2);
		button.setOutlineColor(sf::Color(0, 200, 100));
		okno.draw(button);
	}
	sf::CircleShape yyy(buttonHight / 2,7);
	yyy.setPosition(15 + buttonLenght,5);
	yyy.setFillColor(sf::Color(200, 0, 0));
	okno.draw(yyy);
	sf::RectangleShape Box(sf::Vector2f(buttonLenght, buttonHight));
	Box.setPosition(15 + buttonLenght,5+ 1.5*buttonHight);
	Box.setFillColor(sf::Color(200, 0, 0));
	okno.draw(Box);
	sf::CircleShape circle(buttonHight/2);
	circle.setPosition(15 + buttonLenght,5+ 3*buttonHight);
	circle.setFillColor(sf::Color(200, 0, 0));
	okno.draw(circle);
}
void spawner(sf::RenderWindow &okno, std::vector <box> &boxes , bool &mouseClicked) {
	sf::Vector2i localPosition = sf::Mouse::getPosition(okno);
	bool mouseOnButton;
	for (int i = 0; i < 3; i++) {
		mouseOnButton = (localPosition.x > 10 && localPosition.x < 10 + buttonLenght && localPosition.y>5 + 1.5*i*buttonHight && localPosition.y < 5 + 1.5*i*buttonHight + buttonLenght);
		if (mouseClicked && mouseOnButton) {
			boxes.push_back(box(i, 400 + (boxes.size() % 5)*50, 400));
		}
	}
	mouseClicked = 0;
}
void drawBoxes(sf::RenderWindow &okno, std::vector <box> &boxes) {
	for (int i = 0; i < boxes.size(); i++) {
		if (boxes[i].type == 0) {
			sf::CircleShape yyy(boxes[i].size / 2 ,7);
			yyy.setPosition(boxes[i].posx, boxes[i].posy);
			yyy.setFillColor(sf::Color(0, 0, 200));
			okno.draw(yyy);
		}
		else if (boxes[i].type == 1) {
			sf::RectangleShape Box(sf::Vector2f(boxes[i].size, boxes[i].size));
			Box.setPosition(boxes[i].posx, boxes[i].posy);
			Box.setFillColor(sf::Color(0, 0, 200));
			okno.draw(Box);
		}
		else if (boxes[i].type == 2) {
			sf::CircleShape circle(boxes[i].size / 2);
			circle.setPosition(boxes[i].posx, boxes[i].posy);
			circle.setFillColor(sf::Color(0, 0, 200));
			okno.draw(circle);
		}
	}
}
void magnet(int &lifterPositionx, int &lifterPositiony, std::vector <box> &boxes) {
	bool overlap;
	for (int i = 0; i < boxes.size(); i++) {
		
		overlap = (lifterPositionx > boxes[i].posx && lifterPositionx < boxes[i].posx + boxes[i].size && 130 + lifterPositiony > boxes[i].posy && 130 + lifterPositiony < boxes[i].posy + boxes[i].size);
		if (overlap &&sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && boxes[i].type==1) {
			boxes[i].move();
		}
		else {
			boxes[i].fall();
			boxes[i].collision(boxes, i);
		}

	}
}
