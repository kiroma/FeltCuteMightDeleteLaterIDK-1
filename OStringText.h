#ifndef OSTRINGTEXT_H
#define OSTRINGTEXT_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <sstream>

class OStringText {
	public:
		OStringText(float posX, float posY, unsigned int characterSize, std::string fontFile, sf::Color textColor);
		void updateOText(std::string text, int variable);
		void renderTo(sf::RenderWindow& window);

	private:
		std::ostringstream ssText;
		unsigned int characterSize;

		sf::Font textFont;
		sf::Text text;
};

#endif