#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"
#include "WinMenuState.h"
#include "LoseMenuState.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)  
	: State{ machine, window, replace } {

	//Text information
	this->scoreText = new OStringText(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0 + 30, 25, spaceInvadersFont, sf::Color(255, 255, 255));
	this->verisonText = new Text(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, arialFont, "Version 1.1", sf::Color(255, 255, 0));

	//Score and lives information
	std::ifstream ifs("Information/SpaceInvaders.txt");
	if (!ifs.is_open()) { return; }
	ifs >> playerScore;


	//Player information
	playerTexture.loadFromFile(playerT);
	player = new Player(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.3, 2.0f);
	this->player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
	playerVector.push_back(this->player);
	pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));


	//Invader information
	iBulletTexture.loadFromFile(iBulletT);
	this->iBullet = new InvaderBullet(&iBulletTexture, sf::Vector2<unsigned>(2, 1), 0.1, 2.0f);
	this->iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));

	invaderTexture[0].loadFromFile(invaderT3); //Squid
	invaderTexture[1].loadFromFile(invaderT1); //Crab
	invaderTexture[2].loadFromFile(invaderT2); //Octopus

	//Invader creation
	for (int x = 0; x < invaderCount; x++) {
		if (x <  (invaderCount / rowCount) * 1)										 { this->invaders[x] = new Invaders(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f); this->invaders[x]->setType("squid"); }
		if (x >= (invaderCount / rowCount) * 1 && x < (invaderCount / rowCount) * 2) { this->invaders[x] = new Invaders(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f); this->invaders[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 2 && x < (invaderCount / rowCount) * 3) { this->invaders[x] = new Invaders(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f); this->invaders[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 3 && x < (invaderCount / rowCount) * 4) { this->invaders[x] = new Invaders(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f); this->invaders[x]->setType("octopus"); }
		if (x >= (invaderCount / rowCount) * 4 && x < (invaderCount / rowCount) * 5) { this->invaders[x] = new Invaders(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f); this->invaders[x]->setType("octopus"); }

		this->invaderVector.push_back(this->invaders[x]); 
	}

	//Invader positioning
	//Row 5
	for (int x = (invaderCount / rowCount) * 0; x < (invaderCount / rowCount) * 1; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 150)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 4
	for (int x = (invaderCount / rowCount) * 1; x < (invaderCount / rowCount) * 2; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 220)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 3
	for (int x = (invaderCount / rowCount) * 2; x < (invaderCount / rowCount) * 3; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 290)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 2
	for (int x = (invaderCount / rowCount) * 3; x < (invaderCount / rowCount) * 4; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 360)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 1
	for (int x = (invaderCount / rowCount) * 4; x < (invaderCount / rowCount) * 5; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 430)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;
	

	//Shield information
	for (int x = 0; x < shieldCount; x++) { shieldVector.push_back(&shield[x]); }
	shield[0].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 150));
	shield[1].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 150));
	shield[2].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT - 150));
	shield[3].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 150));



	//UFO information
	ufoVector.push_back(&ufo);
	ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));


	//Sound information
	//0 = Shooting Effect
	//1 = Invader Killed Effect
	//2 = Explosion
	//3 = Ufo Sound Effect
	//4 = Backround Music

	for (int x = 0; x < soundCount; x++) { soundVector.push_back(&playSound[x]); }
	playSound[4].setMusic(backgroundSE, 30, true);
}

PlayingState::~PlayingState() {
	delete this->player;
	delete this->verisonText;
	delete this->scoreText;
	delete this->iBullet;

	for (int x = 0; x < soundCount; x++)		   { playSound[x].stopSound(); playSound[x].stopMusic(); }
	for (int x = 0; x < invaderVector.size(); x++) { delete this->invaders[x]; }
}

void PlayingState::updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space)  { isPlayerShooting = isPressed; }
	if (key == sf::Keyboard::Escape) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); playSound[4].stopMusic(); }
}

void PlayingState::updateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				updateKeyboardInputs(sfEvent.key.code, true);
				break;

			case sf::Event::KeyReleased:
				updateKeyboardInputs(sfEvent.key.code, false);
				break;
		}
	}
}

void PlayingState::update() {
	fpsCounter.updateCounter();
	scoreText->updateOText("SCORE<1>\n\t\t", playerScore);


	/*------------------------------------------------------------------------------------------------------------------*/
	//Updating
	this->player->updateBorderBounds();
	this->player->updatePlayer();
	this->player->updateLives(playerLives);
	pBullet.updateBullet(isPlayerShooting, PLAYER_BULLET_SPEED, this->player->getX(), this->player->getY());

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Invader logic 
	//Collision and Movements 
	for (auto &invader : invaderVector) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader->getX() <= SCREEN_WIDTH * 0 + 40) { isInvaderLeft = false; isInvaderDown = true; }
		if (invader->getX() >= SCREEN_WIDTH)		  { isInvaderLeft = true; isInvaderDown = true; }

		if (enemyKilled < invaderCount - 1) {
			if (isInvaderLeft == false) { invaderMovement.x += INVADER_SPEED; }
			if (isInvaderLeft == true)  { invaderMovement.x -= INVADER_SPEED; }
		}
		else {
			invaderDownTickNum = 300;

			if (isInvaderLeft == false ) { invaderMovement.x += HYPER_INVADER_SPEED; }
			if (isInvaderLeft == true )  { invaderMovement.x -= HYPER_INVADER_SPEED; }
		}

		if (isInvaderDown == true) {
			invaderDownTick++;
			invaderMovement.y += INVADER_SPEED;
			if (invaderDownTick >= invaderDownTickNum) {
				isInvaderDown = false;
				invaderDownTick = 0;
				invaderMovement.y = 0;
			}
		}

		if (invader->isInvaderDead() == false) {
			invader->moveTo(invaderMovement);
			invader->update();
		}
		//Player collision
		if (this->player->collisionWithInvaders(invader)) { playerLives = 0; }

		
		//Bullet collision
		if (pBullet.collisionWithInvaders(invader)) {
			invader->setInvaderPos(sf::Vector2<float>(invader->getX(), invader->getY() - INVADER_ORIGIN));
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			playSound[1].setSound(invaderKilledSE, 25, false);
			enemyKilled++;
			playerScore += invader->returnPointType();;
		}
	}

	//Shooting
	this->iBullet->updateBullet();

	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += INVADER_BULLET_SPEED;
	invaderShooter = randomInvader.getInt(1, invaderCount - 1);

	//Determining which invader is shooting (random)
	if (invaderShooter <= invaderCount) {
		if (this->invaders[invaderShooter]->isInvaderDead()  == false) {
			if (this->iBullet->getX() == BULLET_ORIGIN) { 
				this->iBullet->setBulletPos(sf::Vector2<float>(this->invaders[invaderShooter]->getX(),  this->invaders[invaderShooter]->getY()));
			}
		} 

		else { 
			if (invaderShooter == invaderCount) { invaderShooter += 1; }
			else { invaderShooter == 1; }
		}
	}

	this->iBullet->moveTo(iBulletMovement);

	for (auto &player : playerVector) {
		if (this->iBullet->collisionWithPlayer(player)) {
			this->iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
			playSound[2].setSound(explosionSE, 25, false);
			playerLives--;
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Shield logic
	for (auto &shield : shieldVector) {
		//Collision with player bullets
		if (pBullet.collisionWithShield(shield) || this->iBullet->collisionWithShield(shield)) {
			shield->shieldProtection(1);

			//Collision with player bullets
			if (pBullet.collisionWithShield(shield)) { pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Collision with invader bullets
			else { this->iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Checking for shield damage
			if (shield->shieldProtectionNum() <= 0) { shield->setShieldPos(sf::Vector2<float>(SHIELD_ORIGIN, SHIELD_ORIGIN)); }
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Ufo logic
	sf::Vector2<float> ufoMovement(0.f, 0.f);
	
	ufoTimer = ufoClock.getElapsedTime().asSeconds();
	//Moving Left
	if (ufoTimer >= 15.000 && ufoTimer <= 19.000) {
		ufoMovement.x -= UFO_SPEED;
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); } 
		else {playSound[3].stopSound(); }
	}

	//Moving Right
	if (ufoTimer >= 30.000 && ufoTimer <= 34.000) {
		ufoMovement.x += UFO_SPEED;
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); }
		else { playSound[3].stopSound(); }
	}

	if (ufoTimer >= 35.000) { ufoClock.restart().asSeconds(); }
	ufo.moveTo(ufoMovement);

	//UFO collision
	for (auto &ufo : ufoVector) {
		if (pBullet.collisionWithUFO(ufo)) {
			ufo->setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));
			playSound[1].setSound(invaderKilledSE, 25, false);
			ufoClock.restart().asSeconds();
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			
			//Determining the amount of points given to player after shooting UFO
			randomUFOChoice = randomPoints.getInt(1, 3);
			switch (randomUFOChoice) {
				case 1: ufoPoints = 050; break;
				case 2: ufoPoints = 100; break;
				case 3: ufoPoints = 150; break;
			}
			playerScore += ufoPoints;
		}
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	std::ofstream ofs("Information/SpaceInvaders.txt", std::ios::out | std::ios::ate);

	//Win
	if (enemyKilled == invaderCount) {
		ofs << playerScore;

		machine.run(machine.buildState<PlayingState>(machine, window, true)); playSound[4].stopMusic();
	}

	//Lose
	if (playerLives <= 0) { 
		ofs << 0;

		machine.run(machine.buildState<LoseMenuState>(machine, window, true)); 
		playSound[4].stopMusic(); 
	}

}

void PlayingState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);
	
	this->verisonText->renderTo(window);
	this->scoreText->renderTo(window);
	
	this->player->renderTo(window);
	this->iBullet->renderTo(window);

	pBullet.renderTo(window);
	ufo.renderTo(window);

	for (auto &invader : invaderVector) { invader->renderTo(window); }
	for (auto &shield : shieldVector)	{ shield->renderTo(window); }


	window.display();
}
