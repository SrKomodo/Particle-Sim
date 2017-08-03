#pragma once

class Particle
{
public:
	Particle(sf::Vector2f newPos, sf::Vector2f newVel, double newRadius);
	void draw(sf::RenderWindow &win);
	void updateLogic(float deltaT);

private:
	sf::CircleShape sprite;
	sf::Vector2f pos;
	sf::Vector2f vel;
	double radius;
};

Particle::Particle(sf::Vector2f newPos, sf::Vector2f newVel, double newRadius) {
	sprite = sf::CircleShape(newRadius);
	sprite.setPosition(newPos);

	radius = newRadius;
	pos = newPos;
	vel = newVel;
}

inline void Particle::draw(sf::RenderWindow &win) {
	win.draw(sprite);
}

void Particle::updateLogic(float deltaT) {
	pos += vel * deltaT;
	sprite.setPosition(pos);
}