#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <SFML\Graphics.hpp>

#include "Particle.h"
#include "Game.h"

std::default_random_engine gen((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> posDist(0.f, 300.f);
std::uniform_real_distribution<float> velDist(-1.f, 1.f);

sf::Vector2f randPos() {
	return sf::Vector2f(posDist(gen), posDist(gen));
}

sf::Vector2f randVel() {
	return sf::Vector2f(velDist(gen), velDist(gen));
}

int main() {

	sf::RenderWindow window(sf::VideoMode(300, 300), "Particle Simulator");

	sf::Event event;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);


	std::vector<Particle> particles;
	particles.push_back(Particle(sf::Vector2f(150, 100), sf::Vector2f(0, 0), 5));
	particles.push_back(Particle(sf::Vector2f(150, 200), sf::Vector2f(0, 0), 5));
	/*particles.push_back(Particle(sf::Vector2f(150, 150), sf::Vector2f(0, 0), 10.0));
	for (int i = 0; i < 50; i++) {
		particles.push_back(Particle(randPos(), randVel(), 1));
	}*/

	Game game(particles);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		while (accumulator > ups) {
			accumulator -= ups;
			game.updateLogic();
		}

		window.clear();
		game.draw(&window);
		window.display();
		accumulator += clock.restart();

	}

	return EXIT_SUCCESS;
}