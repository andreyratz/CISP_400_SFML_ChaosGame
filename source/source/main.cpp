// Include important C++ libraries here

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>


#include <iostream>

#include <sstream>

#include <vector>




//Make the code easier to type with "using namespace"

int main() {
	sf::RenderWindow window(sf::VideoMode({200u, 200u}), "works");
	sf::CircleShape shape(100, 50);
	shape.setFillColor(sf::Color::Red);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
}
