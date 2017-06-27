#pragma once
const double G = 6.6742E-11;

class Game {
public:
	Game(std::vector<Particle> particlesToLoad);
	sf::Vector2f getForcesAtPoint(Particle* p1, int pi2);

	void draw(sf::RenderWindow* window);
	void updateLogic();

private:
	float distance(sf::Vector2f p1, sf::Vector2f p2);
	std::vector<Particle> particles;
};

inline Game::Game(std::vector<Particle> particlesToLoad) {
	particles = particlesToLoad;
}

inline sf::Vector2f Game::getForcesAtPoint(Particle* p1, int pi2) {
	sf::Vector2f forces(0, 0);
	for (int pi1 = 0; pi1 < particles.size(); pi1++) {
		Particle* p2 = &particles.at(pi1);
		if (pi1 != pi2) {
			float r = distance(p1->getPosition(), p2->getPosition());

			if (r <= std::max(p1->getMass(), p1->getMass()) / 2) {
				particles.push_back(Particle(p1->getPosition(), sf::Vector2f(0, 0), p1->getMass() + p2->getMass()));
				particles.erase(particles.begin() + pi1);
				particles.erase(particles.begin() + pi2);
			}

			float m1 = p1->getMass();
			float m2 = p2->getMass();

			float f = G * ((m1 * m2) / pow(r, 2));

			sf::Vector2f direction(p1->getPosition() - p2->getPosition());
			float angle = atan2(direction.y, direction.x);
			f *= 100000000000;
			forces -= sf::Vector2f(f * cos(angle), f * sin(angle));
		}
	}
	return sf::Vector2f(forces.x, forces.y);
}

inline void Game::draw(sf::RenderWindow* window) {
	for (Particle &particle : particles) {
		particle.draw(window);
	}
}

inline void Game::updateLogic() {
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i).updateLogic(getForcesAtPoint(&particles.at(i), i));
	}
}

inline float Game::distance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrtf(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}