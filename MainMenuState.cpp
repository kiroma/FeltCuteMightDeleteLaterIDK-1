#include "MainMenuState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "PlayingState.h"
#include "MoreInfo.h"

#include <iostream>
#include <fstream>


MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace } {
	//Buttons
	this->quitGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300, 100, 40, 30, spaceInvadersFont, "Quit",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255));

	this->startGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 100, 40, 30, spaceInvadersFont, "Play",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255));
	
	//Text
	this->titleText = new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 20, 50, spaceInvadersFont, "Space Invaders", sf::Color(255, 255, 255));

	this->ufoText = new Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 - 040, 20, spaceInvadersFont, " = ? MYSTERY", sf::Color(255, 255, 255));
	this->t1Text  = new Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 040, 20, spaceInvadersFont, " = 30 Points", sf::Color(255, 255, 255));
	this->t2Text  = new Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 140, 20, spaceInvadersFont, " = 20 Points", sf::Color(255, 255, 255));
	this->t3Text  = new Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 240, 20, spaceInvadersFont, " = 10 Points", sf::Color(0, 128, 0));



	//Textures
	invaderTexture[0].loadFromFile(invaderT3);
	invaderTexture[1].loadFromFile(invaderT1);
	invaderTexture[2].loadFromFile(invaderT2);
	ufoTexture.loadFromFile(UFOT);

	for (int x = 0; x < 3; x++) {
		invaders[x].setTexture(invaderTexture[x]);
		invaders[x].setTextureRect(sf::IntRect(invaderTexture[x].getSize().x / 2 * 0, invaderTexture[x].getSize().y * 0, invaderTexture[x].getSize().x / 2, invaderTexture[x].getSize().y));
		invaders[x].setPosition(sf::Vector2<float>(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2.5 + 30 + invaderYPosAdd));
		invaderYPosAdd += 100;
		if (x == 2) { invaders[x].setColor(sf::Color(0, 128, 0)); }
	}

	ufo.setTexture(ufoTexture);
	ufo.setPosition(sf::Vector2<float>(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2.5 - 70));
	ufo.setScale(1 * 1.5, 1 * 1.5);
}

MainMenuState::~MainMenuState() {
	delete this->quitGameButton;
	delete this->startGameButton;
	delete this->titleText;

	delete this->ufoText;
	delete this->t1Text;
	delete this->t2Text;
	delete this->t3Text;
}

void MainMenuState::updateEvents() {
	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);

	//Updating mouse position for button functionality
	this->quitGameButton->update(sf::Vector2<float>(mousePos));
	this->startGameButton->update(sf::Vector2<float>(mousePos));

	//Events while loop
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (this->quitGameButton->isPressed() == true) { machine.quit(); }
			if (this->startGameButton->isPressed() == true) { machine.run(machine.buildState<PlayingState>(machine, window, true)); }
			break;
		}
	}
}

void MainMenuState::update() {
	fpsCounter.updateCounter();
}

void MainMenuState::render() {
	window.clear();

	//Render items
	this->quitGameButton->renderTo(window);
	this->startGameButton->renderTo(window);
	this->titleText->renderTo(window);
	
	this->ufoText->renderTo(window);
	this->t1Text->renderTo(window);
	this->t2Text->renderTo(window);
	this->t3Text->renderTo(window);

	fpsCounter.renderTo(window);

	for (int x = 0; x < 3; x++) { window.draw(invaders[x]); }
	window.draw(ufo);

	window.display();
}
