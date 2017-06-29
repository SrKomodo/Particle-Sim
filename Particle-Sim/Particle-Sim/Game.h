#pragma once
const double G = 6.6742E-11;

class Game {
public:
	Game(std::vector<Particle> particlesToLoad);
	sf::Vector2f getForcesAtPoint(Particle* p1, int pi2);

	void draw(sf::RenderTexture* window);
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

			if (r <= std::max(p1->getMass(), p1->getMass()) * 4) {
				/*std::cout
					<< "Colission!" << std::endl
					<< "=================" << std::endl
					<< "Particle 1" << std::endl
					<< "Position: " << p1->getPosition().x << " " << p1->getPosition().y << std::endl
					<< "Velocity: " << p1->getVelocity().x << " " << p1->getVelocity().y << std::endl
					<< "Mass: " << p1->getMass() << std::endl
					<< "=================" << std::endl
					<< "Particle 2" << std::endl
					<< "Position: " << p2->getPosition().x << " " << p2->getPosition().y << std::endl
					<< "Velocity: " << p2->getVelocity().x << " " << p2->getVelocity().y << std::endl
					<< "Mass: " << p2->getMass() << std::endl;*/
				p1->setPosition(sf::Vector2f(
					(p1->getPosition().x + p2->getPosition().x) / 2,
					(p1->getPosition().y + p2->getPosition().y) / 2
				));
				p1->setVelocity(p1->getVelocity() + p2->getVelocity());
				p1->setMass(p1->getMass() + p2->getMass());
				/*std::cout
					<< "=================" << std::endl
					<< "New Particle" << std::endl
					<< "Position: " << p1->getPosition().x << " " << p1->getPosition().y << std::endl
					<< "Velocity: " << p1->getVelocity().x << " " << p1->getVelocity().y << std::endl
					<< "Mass: " << p1->getMass() << std::endl << std::endl;*/
				particles.erase(particles.begin() + pi2);
			}

			float m1 = p1->getMass();
			float m2 = p2->getMass();

			float f = G * ((m1 * m2) / pow(r, 2));

			sf::Vector2f direction(p1->getPosition() - p2->getPosition());
			float angle = atan2(direction.y, direction.x);
			f *= simSpeed;
			forces -= sf::Vector2f(f * cos(angle), f * sin(angle));
		}
	}
	return sf::Vector2f(forces.x, forces.y);
}

inline void Game::draw(sf::RenderTexture* window) {
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