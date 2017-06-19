#include <iostream>
#include <random>
#include <SFML\Graphics.hpp>

#include "Particle.h"
#include "Game.h"

int main() {

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.f, 300.f);

	sf::RenderWindow window(sf::VideoMode(300, 300), "Particle Simulator");

	sf::Event event;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	Game game;

	std::vector<Particle> particles;
	for (int i = 0; i < 10; i++) {
		particles.push_back(Particle(sf::Vector2f(distribution(generator), distribution(generator)), &game));
	}

	game.loadParticles(particles);

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