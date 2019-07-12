#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"
#include "WinMenuState.h"
#include "LoseMenuState.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)  
	: State{ machine, window, replace },
	versionText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, arialFont, "Version 1.1", sf::Color(255, 255, 0)),
	scoreText(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0 + 30, 25, spaceInvadersFont, sf::Color(255, 255, 255))
{
	//Score and lives information
	std::ifstream ifs("Information/SpaceInvaders.txt");
	if (!ifs.is_open()) 
	{
		ifs >> playerScore;
	}

	//Player information
	playerTexture.loadFromFile(playerT);
	players.emplace_back(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.3, 2.0f);
	players[0].setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
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
		if (x <  (invaderCount / rowCount) * 1)
		{
			invaders.emplace_back(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f);
			invaders[x].setType("squid");
		}
		if (x >= (invaderCount / rowCount) * 1 && x < (invaderCount / rowCount) * 2)
		{
			invaders.emplace_back(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f);
			invaders[x].setType("crab");
		}
		if (x >= (invaderCount / rowCount) * 2 && x < (invaderCount / rowCount) * 3)
		{
			invaders.emplace_back(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f);
			invaders[x].setType("crab");
		}
		if (x >= (invaderCount / rowCount) * 3 && x < (invaderCount / rowCount) * 4)
		{
			invaders.emplace_back(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f);
			invaders[x].setType("octopus");
		}
		if (x >= (invaderCount / rowCount) * 4 && x < (invaderCount / rowCount) * 5) {
			invaders.emplace_back(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f);
			invaders[x].setType("octopus");
		}

	}

	//Invader positioning
	//Row 5
	for (int x = (invaderCount / rowCount) * 0; x < (invaderCount / rowCount) * 1; x++)
	{
		invaders[x].setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 150));
		changedInvaderX += 80;
	}
	changedInvaderX = initialInvaderX;

	//Row 4
	for (int x = (invaderCount / rowCount) * 1; x < (invaderCount / rowCount) * 2; x++)
	{
		invaders[x].setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 220));
		changedInvaderX += 80;
	}
	changedInvaderX = initialInvaderX;

	//Row 3
	for (int x = (invaderCount / rowCount) * 2; x < (invaderCount / rowCount) * 3; x++)
	{
		invaders[x].setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 290));
		changedInvaderX += 80;
	}
	changedInvaderX = initialInvaderX;

	//Row 2
	for (int x = (invaderCount / rowCount) * 3; x < (invaderCount / rowCount) * 4; x++)
	{
		invaders[x].setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 360));
		changedInvaderX += 80;
	}
	changedInvaderX = initialInvaderX;

	//Row 1
	for (int x = (invaderCount / rowCount) * 4; x < (invaderCount / rowCount) * 5; x++)
	{
		invaders[x].setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 430));
		changedInvaderX += 80;
	}
	changedInvaderX = initialInvaderX;
	

	//Shield information
	shields[0].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 150));
	shields[1].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 150));
	shields[2].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT - 150));
	shields[3].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 150));



	//UFO information
	ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));


	//Sound information
	//0 = Shooting Effect
	//1 = Invader Killed Effect
	//2 = Explosion
	//3 = Ufo Sound Effect
	//4 = Backround Music

	playSound[4].setMusic(backgroundSE, 30, true);
}

PlayingState::~PlayingState() {
	delete this->iBullet;

	for (int x = 0; x < soundCount; x++)		   { playSound[x].stopSound(); playSound[x].stopMusic(); }
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
	scoreText.updateOText("SCORE<1>\n\t\t", playerScore);


	/*------------------------------------------------------------------------------------------------------------------*/
	//Updating
	players[0].updateBorderBounds();
	players[0].updatePlayer();
	players[0].updateLives(playerLives);
	pBullet.updateBullet(isPlayerShooting, PLAYER_BULLET_SPEED, players[0].getX(), players[0].getY());

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Invader logic 
	//Collision and Movements 
	for (auto &invader : invaders) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader.getX() <= SCREEN_WIDTH * 0 + 40) { isInvaderLeft = false; isInvaderDown = true; }
		if (invader.getX() >= SCREEN_WIDTH)		  { isInvaderLeft = true; isInvaderDown = true; }

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

		if (invader.isInvaderDead() == false) {
			invader.moveTo(invaderMovement);
			invader.update();
		}
		//Player collision
		if (players[0].collisionWithInvaders(&invader)) { playerLives = 0; }

		
		//Bullet collision
		if (pBullet.collisionWithInvaders(&invader)) {
			invader.setInvaderPos(sf::Vector2<float>(invader.getX(), invader.getY() - INVADER_ORIGIN));
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			playSound[1].setSound(invaderKilledSE, 25, false);
			enemyKilled++;
			playerScore += invader.returnPointType();
		}
	}

	//Shooting
	this->iBullet->updateBullet();

	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += INVADER_BULLET_SPEED;
	invaderShooter = randomInvader.getInt(1, invaderCount - 1);

	//Determining which invader is shooting (random)
	if (invaderShooter <= invaderCount) {
		if (invaders[invaderShooter].isInvaderDead()  == false) {
			if (this->iBullet->getX() == BULLET_ORIGIN) { 
				this->iBullet->setBulletPos(sf::Vector2<float>(invaders[invaderShooter].getX(), invaders[invaderShooter].getY()));
			}
		} 

		else { 
			if (invaderShooter == invaderCount) { invaderShooter += 1; }
			else { invaderShooter = 1; }
		}
	}

	this->iBullet->moveTo(iBulletMovement);

	for (auto &player : players) {
		if (this->iBullet->collisionWithPlayer(&player)) {
			this->iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			player.setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
			playSound[2].setSound(explosionSE, 25, false);
			playerLives--;
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Shield logic
	for (auto &shield : shields) {
		//Collision with player bullets
		if (pBullet.collisionWithShield(&shield) || this->iBullet->collisionWithShield(&shield)) {
			shield.shieldProtection(1);

			//Collision with player bullets
			if (pBullet.collisionWithShield(&shield)) { pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Collision with invader bullets
			else { iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Checking for shield damage
			if (shield.shieldProtectionNum() <= 0) { shield.setShieldPos(sf::Vector2<float>(SHIELD_ORIGIN, SHIELD_ORIGIN)); }
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
	if (pBullet.collisionWithUFO(&ufo)) {
		ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));
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

	versionText.renderTo(window);
	scoreText.renderTo(window);

	players[0].renderTo(window);
	iBullet->renderTo(window);

	pBullet.renderTo(window);
	ufo.renderTo(window);

	for (auto &invader : invaders) { invader.renderTo(window); }
	for (auto &shield : shields) { shield.renderTo(window); }


	window.display();
}
