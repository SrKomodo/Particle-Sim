#pragma once

class Particle {
public:
	Particle();
	Particle(sf::Vector2f pos, sf::Vector2f velToLoad, float massToLoad);

	void draw(sf::RenderWindow* window);
	void updateLogic(sf::Vector2f forces);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getMass();

	void setPosition(sf::Vector2f posToLoad);
	void setVelocity(sf::Vector2f velToLoad);
	void setMass(float massToLoad);

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

inline Particle::Particle(sf::Vector2f posToLoad, sf::Vector2f velToLoad, float massToLoad) {
	sprite = sf::CircleShape(massToLoad * 2);
	sprite.setOrigin(sf::Vector2f(massToLoad * 2, massToLoad * 2));
	sprite.setPosition(pos);
	pos = posToLoad;
	vel = velToLoad;
	mass = massToLoad;
}

inline void Particle::draw(sf::RenderWindow* window) {
	window->draw(sprite);
}

inline void Particle::updateLogic(sf::Vector2f forces) {
	vel += forces;
	pos += vel;
	sprite.setPosition(pos);
}

inline sf::Vector2f Particle::getPosition() { return pos; }
inline sf::Vector2f Particle::getVelocity() { return vel; }
inline float Particle::getMass() { return mass; }

inline void Particle::setPosition(sf::Vector2f posToLoad) { pos = posToLoad; }
inline void Particle::setVelocity(sf::Vector2f velToLoad) { vel = velToLoad; }
inline void Particle::setMass(float massToLoad) {
	mass = massToLoad;
	sprite.setRadius(massToLoad * 2);
}