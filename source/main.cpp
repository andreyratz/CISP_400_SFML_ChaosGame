// Include important C++ libraries here

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PFRAME 5

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode({200u, 200u}), "Chaos Game");

	sf::Font nerd("3270NerdFont-Regular.ttf");

	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> points;
	sf::Color awesome(137, 126, 248, 0);
	//optimal ratio suuper important
	double r = 0;
	int index;
	int previous = -1;

	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
			window.close();
		}
		
		//event handler
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				const auto* m = event->getIf<sf::Event::MouseButtonPressed>();
    				if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
        				/*std::cout << "the left button was pressed" << std::endl;
        				std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
        				std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;*/

					vertices.push_back(sf::Vector2f(m->position.x, m->position.y));
    				}
			}

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
					points.push_back(vertices[vertices.size() - 1]);
					// I was originally going to use some weird formula but I found this on wikipedia
					// https://en.wikipedia.org/wiki/Chaos_game
					if (vertices.size() % 4 == 0)
						r = 1/(1+tan(3.1416/vertices.size()));
					if (vertices.size() % 4 == 1 || vertices.size() % 4 == 3)
						r = 1/(1 + (1 + 2*sin(3.1416/(2*vertices.size()))));
					if (vertices.size() % 4 == 2)
						r = 1/(1 + sin(3.1416/vertices.size()));

				//std::cout << "r " << r << std::endl;
				}
			}
		}

		window.clear();
		
		sf::Text text(nerd);
		if (vertices.size() == 0 || points.size() == 0) {
			text.setString("Click as many points as you want to make a shape, \nthen one point within the shape you made.");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			window.draw(text);
		}
		
		if (points.size() > 0) {
			for (int i = 0; i < PFRAME; i++) { 
				sf::Vector2f nextPoint;

				int vertex = rand() % vertices.size();

				if (vertices.size() > 3 && (vertex == previous)) {
					while (vertex == previous) {
						vertex = rand() % vertices.size();
					}
				}

				previous = vertex;
				
				nextPoint.x = (vertices[vertex].x * r) + (points[index].x * (1 - r));
				nextPoint.y = (vertices[vertex].y * r) + (points[index].y * (1 - r));
				points.push_back(nextPoint);
				index++;

			}
		}


		if (vertices.size() > 0 && points.size() == 0) {
			for (int i = 0; i < vertices.size(); i++) {
				sf::CircleShape circle(5.f);
				circle.setPosition(sf::Vector2f(vertices[i].x, vertices[i].y));
				circle.setFillColor(sf::Color::White);
				window.draw(circle);

			}
		}

		for (int i = 0; i < points.size(); i++) {
			sf::RectangleShape rectangle(sf::Vector2f(10,10));
			rectangle.setPosition(sf::Vector2f(points[i].x, points[i].y));
			rectangle.setFillColor(sf::Color::White);
			rectangle.setSize(sf::Vector2f(2,2));
			window.draw(rectangle);
		}

		window.display();

	}
}
