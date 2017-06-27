#pragma once

class Particle {
public:
	Particle();
	Particle(sf::Vector2f pos, sf::Vector2f velToLoad, float massToLoad, unsigned int idToLoad);

	void draw(sf::RenderWindow* window);
	void updateLogic(sf::Vector2f forces);

	sf::Vector2f getPosition();
	float getMass();
	unsigned int id;

private:
	float mass;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::CircleShape sprite;
};

inline Particle::Particle() {
	sprite = sf::CircleShape(5.0f);
	sprite.setOrigin(sf::Vector2f(2.5f, 2.5f));
	pos = sf::Vector2f(0, 0);
	vel = sf::Vector2f(0, 0);
	mass = 1;
}

inline Particle::Particle(sf::Vector2f posToLoad, sf::Vector2f velToLoad, float massToLoad, unsigned int idToLoad) {
	sprite = sf::CircleShape(5.0f);
	sprite.setPosition(pos);
	pos = posToLoad;
	vel = velToLoad;
	mass = massToLoad;
	id = idToLoad;
	sprite.setOrigin(sf::Vector2f(2.5f, 2.5f));
}

inline void Particle::draw(sf::RenderWindow* window) {
	window->draw(sprite);
}

inline void Particle::updateLogic(sf::Vector2f forces) {
	vel += forces;
	pos += vel;
	sprite.setPosition(pos);
}

inline sf::Vector2f Particle::getPosition() {
	return pos;
}

inline float Particle::getMass() {
	return mass;
}