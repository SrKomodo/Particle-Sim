#pragma once
#include "Game.h"

class Particle {
public:
	Particle(sf::Vector2f pos, Game* gameToLoad);

	void draw(sf::RenderWindow* window);
	void updateLogic();

private:
	sf::CircleShape sprite;
};

inline Particle::Particle(sf::Vector2f pos, Game* gameToLoad) {

	sprite = sf::CircleShape(5.0f);
	sprite.setPosition(pos);
	sprite.setOrigin(sf::Vector2f(2.5f, 2.5f));
}

inline void Particle::draw(sf::RenderWindow* window) {
	window->draw(sprite);
}

inline void Particle::updateLogic() {

}