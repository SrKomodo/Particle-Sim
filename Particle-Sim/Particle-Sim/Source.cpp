#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

#include "Game.h"
#include "Particle.h"

std::default_random_engine gen((int)std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> posDist(-240, 240);
std::uniform_real_distribution<float> velDist(-20, 20);

sf::Vector2f randPos() {
	return sf::Vector2f(posDist(gen), posDist(gen));
}

sf::Vector2f randVel() {
	return sf::Vector2f(velDist(gen), velDist(gen));
}

int main() {

	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow win(sf::VideoMode(640, 480), "Pain", sf::Style::Default, settings);
	win.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(640, 480)));

	vector<Particle> particles;

	/*for (int i = 0; i < 10; i++) {
		particles.push_back(Particle(randPos(), randVel(), 10, 1));
	}*/

	//particles.push_back(Particle(sf::Vector2f(-50, 0), sf::Vector2f(20, 0), 10, 1));
	//particles.push_back(Particle(sf::Vector2f(50, 0), sf::Vector2f(-20, 0), 10, 1));
	
	particles.push_back(Particle(sf::Vector2f(-50, 50), sf::Vector2f(0, 20), 10, 1));
	particles.push_back(Particle(sf::Vector2f(50, 50), sf::Vector2f(-20, 20), 10, 1));

	Game game(std::move(particles));

	while (win.isOpen()) {
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				win.close();
			}
		}

		float deltaT = clock.restart().asSeconds();
		game.update(deltaT);

		win.clear();
		game.draw(win);
		win.display();
	}

	return EXIT_SUCCESS;
}