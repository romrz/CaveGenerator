#include "MapGenerator.h"
#include <iostream>
#include <SFML/System.hpp>

int main() {
	MapGenerator generator(130, 40);
	generator.setIterations(6);
	generator.setDeathThreshold(3);
	generator.setBirthThreshold(4);
	generator.setStartAlive(50);

	int seed;
	while (true) {
		std::cout << "Seed: ";
		std::cin >> seed;
		if (seed < 0) break;
		generator.setSeed(seed);
		sf::Clock clock;
		generator.generate();
		std::cout << "Time: " << clock.restart().asMilliseconds() << std::endl;
		generator.print();
	}
	return 0;
}