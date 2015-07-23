#include "MapGenerator.h"
#include "TileMap.h"
#include <iostream>

void processInput(sf::RenderWindow& window);

bool generateLevel = true;

int main() {
	sf::Vector2i levelSize(30, 20);
	sf::Vector2i tileSize(32, 32);
	sf::RenderWindow window(sf::VideoMode(levelSize.x * tileSize.x, levelSize.y * tileSize.y), "Cellular Automata Cave Generation");
	window.setVerticalSyncEnabled(true);

	sf::Texture texture;
	if (!texture.loadFromFile("tileset.png")) {
		std::cout << "Unable to load the texture" << std::endl;
		return 0;
	}
	Tile tileset[] = {
		Tile(texture, sf::IntRect(tileSize.x, 0, tileSize.x, tileSize.y)),
		Tile(texture, sf::IntRect(0, 0, tileSize.x, tileSize.y))
	};

	sf::Font font;
	if (!font.loadFromFile("LCD_Solid.TTF")) {
		std::cout << "Unable to load the font" << std::endl;
		return 0;
	}
	sf::String str(" FPS\n\nPRESS 'G' TO GENERATE A NEW CAVE");
	sf::Text text(str, font, 10);
	text.setPosition(10, 10);
	text.setColor(sf::Color::White);

	TileMap tileMap(levelSize, tileSize, tileset);
	MapGenerator generator(levelSize.x, levelSize.y);
	generator.setIterations(4);
	generator.setDeathThreshold(3);
	generator.setBirthThreshold(4);
	generator.setChanceToStartAlive(50);
	
	int frameCount = 0;
	sf::Clock clock;
	while (window.isOpen()) {
		if (clock.getElapsedTime().asMilliseconds() >= 1000) {
			clock.restart();
			text.setString(std::to_string(frameCount) + str);
			frameCount = 0;
		}
		frameCount++;
		if (generateLevel) {
			tileMap.setMap(generator.generate());
			generateLevel = false;
		}
		processInput(window);
		window.draw(tileMap);
		window.draw(text);
		window.display();
	}
	return 0;
}

void processInput(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::G)
				generateLevel = true;
}