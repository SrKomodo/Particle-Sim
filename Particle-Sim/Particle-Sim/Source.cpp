#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <SFML\Graphics.hpp>

#include "Particle.h"
#include "Game.h"

std::default_random_engine gen((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> posDist(-1500.f, 1500.f);
std::uniform_real_distribution<float> velDist(-1.f / 100000000, 1.f / 100000000);

sf::Vector2f randPos() {
	return sf::Vector2f(posDist(gen), posDist(gen));
}

sf::Vector2f randVel() {
	return sf::Vector2f(velDist(gen), velDist(gen));
}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Particle Simulator", sf::Style::Default, settings);
	sf::View view(window.getDefaultView());
	view.setCenter(sf::Vector2f(0, 0));
	window.setView(view);

	sf::Event event;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	float zoom = 1;

	std::vector<Particle> particles;
	//particles.push_back(Particle(sf::Vector2f(100, -100), sf::Vector2f(0, 0), 10));
	//particles.push_back(Particle(sf::Vector2f(100, 100), sf::Vector2f(0, 0), 50));
	for (int i = 0; i < 50; i++) {
		particles.push_back(Particle(randPos(), randVel(), 10));
	}
	particles.push_back(Particle(sf::Vector2f(10000000, 10000000), sf::Vector2f(10000, 0), 1));

	Game game(particles);
	game.simSpeed = 100000;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseWheelMoved:
				if (event.mouseWheel.delta > 0) {
					view.zoom(0.8);
					zoom *= 0.8;
				}
				else {
					view.zoom(1.2);
					zoom *= 1.2;
				}
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Z) {
					game.simSpeed *= 10;
				}
				else if (event.key.code == sf::Keyboard::X) {
					game.simSpeed /= 10;
				}
			}
		}
		//kill me pls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			view.move(sf::Vector2f(-.5 * zoom, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(sf::Vector2f(.5 * zoom, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.move(sf::Vector2f(0, -.5 * zoom));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			view.move(sf::Vector2f(0, .5 * zoom));
		}
		window.setView(view);


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