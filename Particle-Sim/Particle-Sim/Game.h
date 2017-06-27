#pragma once
const double G = 6.6742E-11;

class Game {
public:
	Game(std::vector<Particle> particlesToLoad);
	sf::Vector2f getForcesAtPoint(Particle* p1);

	void draw(sf::RenderWindow* window);
	void updateLogic();

private:
	float distance(sf::Vector2f p1, sf::Vector2f p2);
	std::vector<Particle> particles;
};

inline Game::Game(std::vector<Particle> particlesToLoad) {
	particles = particlesToLoad;
}

inline sf::Vector2f Game::getForcesAtPoint(Particle* p1) {
	sf::Vector2f forces(0, 0);
	for (Particle &p2 : particles) {
		if (p2.id != p1->id) {
			float m1 = p1->getMass();
			float m2 = p2.getMass();
			float r = distance(p1->getPosition(), p2.getPosition());

			float f = G * ((m1 * m2) / pow(r, 2));

			sf::Vector2f direction(p1->getPosition() - p2.getPosition());
			float angle = atan2(direction.y, direction.x);
			/*std::cout << m1 << " " << m2 << std::endl << r << std::endl << f << std::endl;
			std::system("pause >nul");*/
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
	for (Particle &particle : particles) {
		particle.updateLogic(getForcesAtPoint(&particle));
	}
}

inline float Game::distance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrtf(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}