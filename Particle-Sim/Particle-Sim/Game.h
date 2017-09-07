#pragma once

#include <vector>
#include "Particle.h"

using namespace std;

class Game
{
public:
	Game(vector<Particle>&& newParticles) : particles(std::move(newParticles)){
		
	};
	void draw(sf::RenderWindow &win);
	void update(float deltaT);

private:
	vector<Particle> particles;
};

inline void Game::draw(sf::RenderWindow &win) {
	for (Particle &particle : particles) {
		particle.draw(win);
	}
}

inline void Game::update(float deltaT) {
	for (Particle &p1 : particles) {
		for (Particle &p2 : particles) {
			if (p1 != p2) {
				p1.calculateCollision(p2);
			}
		}
	}
	for (Particle &particle : particles) {
		particle.updateLogic(deltaT);
	}
}