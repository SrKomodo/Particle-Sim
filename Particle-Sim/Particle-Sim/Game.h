#pragma once

class Game {
public:
	Game();
	sf::Vector2f getForcesAtPoint(sf::Vector2f pos);

	void loadParticles(std::vector<Particle> particlesToLoad);

	void draw(sf::RenderWindow* window);
	void updateLogic();

private:
	std::vector<Particle> particles;
};


inline void Game::loadParticles(std::vector<Particle> particlesToLoad) {
	particles = particlesToLoad;
}

inline Game::Game() {}

inline sf::Vector2f Game::getForcesAtPoint(sf::Vector2f pos) {
	return sf::Vector2f(0, 0);
}

inline void Game::draw(sf::RenderWindow* window) {
	for (Particle particle : particles) {
		particle.draw(window);
	}
}

inline void Game::updateLogic() {
	for (Particle particle : particles) {
		particle.updateLogic();
	}
}