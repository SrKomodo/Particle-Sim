#pragma once

class Particle
{
public:
	Particle(sf::Vector2f newPos, sf::Vector2f newVel, float newRadius, double newMass);
	void draw(sf::RenderWindow &win);
	void updateLogic(float deltaT);
	void calculateCollision(Particle &p2);

	bool operator==(const Particle& rhs);
	inline bool operator!=(const Particle& rhs) { return !operator==(rhs); }

	sf::Vector2f getPos();

private:
	sf::CircleShape sprite;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f collisionVel;
	bool collided = false;
	double radius;
	double mass;
};

Particle::Particle(sf::Vector2f newPos, sf::Vector2f newVel, float newRadius, double newMass) {
	sprite = sf::CircleShape(newRadius);
	sprite.setOrigin(sf::Vector2f(newRadius, newRadius));
	sprite.setPosition(newPos);

	radius = newRadius;
	mass = newMass;
	pos = newPos;
	vel = newVel;
}

inline void Particle::draw(sf::RenderWindow &win) {
	win.draw(sprite);
}

void Particle::updateLogic(float deltaT) {
	if (collided) {
		vel = collisionVel;
		collided = false;
	}
	pos += vel * deltaT;
	sprite.setPosition(pos);
}

void Particle::calculateCollision(Particle &p2){
	float dx = pos.x - p2.pos.x;
	float dy = pos.y - p2.pos.y;
	float distance = sqrtf(dx * dx + dy * dy);

	if (distance <= radius + p2.radius) {
		collided = true;

		float θ1 = atan2(vel.y, vel.x);
		float θ2 = atan2(p2.vel.y, p2.vel.x);

		float v1 = sqrt(pow(vel.x, 2) + pow(vel.y, 2));
		float v2 = sqrt(pow(p2.vel.x, 2) + pow(p2.vel.y, 2));

		collisionVel = sf::Vector2f((vel.x * (mass - p2.mass) + (2 * p2.mass * p2.vel.x)) / (mass + p2.mass), (vel.y * (mass - p2.mass) + (2 * p2.mass * p2.vel.y)) / (mass + p2.mass));
	}
}

inline bool Particle::operator==(const Particle & rhs) {
	return pos.x == rhs.pos.x && pos.y == rhs.pos.y;
}

inline sf::Vector2f Particle::getPos() {
	return pos;
}
