#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Vector2.hpp"

#include "FPSCounter.h"
#include "Text.h"
#include "MoreInfo.h"
#include "Random.h"
#include "PlaySound.h"
#include "OStringText.h"

#include "Player.h"
#include "Invaders.h"
#include "PlayerBullet.h"
#include "InvaderBullet.h"
#include "Shield.h"
#include "UFO.h"

#include "State.h"
#include "MainMenuState.h"
class StateMachine;

#include <iostream>
#include <fstream>

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~PlayingState();

		void updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();
		
	private:
		//Variables and Booleans
		static const int invaderCount = 55;
		static const int shieldCount  = 4;
		static const int soundCount   = 5;
		static const int rowCount     = 5;
		float invaderSwitchTimer      = 0.45;
		unsigned int pBulletCount	  = 0;
		const int initialInvaderX	  = 100;
		int changedInvaderX			  = 100;

		int enemyKilled		   = 0;
		int invaderShooter	   = 0;
		int playerLives		   = 3;
		int playerScore		   = 0;
		int randomUFOChoice    = 0;
		int ufoPoints		   = 0;
		int invaderDownTick    = 0;
		int invaderDownTickNum = 100;
		int shieldProtection   = SHIELD_PROTECTION;
		
		bool isPlayerShooting = false;
		bool isInvaderLeft	  = false;
		bool isInvaderDown    = false;
		
		//Vectors
		std::vector<PlaySound*> soundVector;
		std::vector<Player*> playerVector;
		std::vector<Invaders*> invaderVector;
		std::vector<Shield*> shieldVector;
		std::vector<UFO*> ufoVector;


		//Class objects
		Random<> randomInvader, randomPoints;
		FPSCounter fpsCounter;
		Text* verisonText;
		PlaySound playSound[soundCount];
		OStringText* scoreText;
		Player* player;
		Invaders* invaders[invaderCount];
		PlayerBullet pBullet;
		InvaderBullet* iBullet;
		Shield shield[shieldCount];
		UFO ufo;



		//SFML
		sf::Event sfEvent;
		sf::Texture playerTexture, invaderTexture[3], iBulletTexture;
		sf::Clock dtClock, ufoClock;
		float	  dtTimer, ufoTimer;
};

#endif