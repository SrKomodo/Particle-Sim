#pragma once
const double G = 6.6742E-11;

class Game {
public:
	Game(std::vector<Particle> particlesToLoad);
	sf::Vector2f getForcesAtPoint(Particle* p1, int pi2);

	void draw(sf::RenderWindow* window);
	void updateLogic();

	float simSpeed;

private:
	float distance(sf::Vector2f p1, sf::Vector2f p2);
	std::vector<Particle> particles;
};

inline Game::Game(std::vector<Particle> particlesToLoad) {
	particles = particlesToLoad;
	simSpeed = 10;
}

sf::Vector2f Game::getForcesAtPoint(Particle* p1, int pi1) {
	sf::Vector2f forces(0, 0);
	for (int pi2 = 0; pi2 < particles.size(); pi2++) {
		Particle* p2 = &particles.at(pi2);
		if (pi1 != pi2) {
			float r = distance(p1->getPosition(), p2->getPosition());

			float m1 = p1->getMass();
			float m2 = p2->getMass();

			if (r <= p1->getMass() * 2 + p2->getMass() * 2) {

				p1->setMass(p1->getMass() + p2->getMass());

				p1->setPosition(sf::Vector2f(
					((p1->getPosition().x * p1->getMass()) + (p2->getPosition().x * p2->getMass())) / (p1->getMass() + p2->getMass()),
					((p1->getPosition().y * p1->getMass()) + (p2->getPosition().y * p2->getMass())) / (p1->getMass() + p2->getMass())
				));

				p1->setVelocity(sf::Vector2f(
					p1->getMass() / p1->getVelocity().x + p2->getMass() / p2->getVelocity().x,
					p1->getMass() / p1->getVelocity().y + p2->getMass() / p2->getVelocity().y
				));

				particles.erase(particles.begin() + pi2);
			}

			float f = G * ((m1 * m2) / pow(r, 2));

			sf::Vector2f direction(p1->getPosition() - p2->getPosition());
			float angle = atan2(direction.y, direction.x);
			f *= simSpeed;
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
		particles.at(i).id = i;
	}
	for (int i = 0; i < particles.size(); i++) {
		if (particles.at(i).id == i) {
			particles.at(i).updateLogic(getForcesAtPoint(&particles.at(i), i), simSpeed);
		}
	}
}

inline float Game::distance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrtf(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}