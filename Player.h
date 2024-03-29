#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"
#include "ToggleKey.h"
#include "OStringText.h"
#include "Invaders.h"

#include <iostream>

class Player {
	public:
		Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void renderTo(sf::RenderWindow& window);
		void setPlayerPos(sf::Vector2<float> newPos);
		void updatePlayer();
		void updateLives(int lives);

		int getX();
		int getY();
		void updateBorderBounds();
		sf::FloatRect getGlobalBounds();

		bool collisionWithInvaders(Invaders* invaders);

	private:
		OStringText* playerLivesText;

		Animation animation;
		float speed;

		sf::Sprite player;
};

#endif