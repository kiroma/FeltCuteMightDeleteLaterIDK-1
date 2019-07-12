#ifndef MOREINFO_H
#define MOREINFO_H

//General
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 900
#define FRAMERATE_LIMIT 120

//Variables
#define GROUND_HEIGHT 800
#define PLAYER_BORDER_SPEED 30
#define INVADER_ORIGIN 10000
#define SHIELD_ORIGIN 15000
#define BULLET_ORIGIN 12345

#define UFO_SPEED 3.0
#define INVADER_SPEED 2.0
#define HYPER_INVADER_SPEED 10.0
#define PLAYER_BULLET_SPEED 5.0
#define INVADER_BULLET_SPEED 2.0
#define PLAYER_SPEED 1.2

#define SHIELD_PROTECTION 10

//Fonts
#define arialFont "res/fonts/arial.ttf"
#define spaceInvadersFont "res/fonts/space_invaders.ttf"

//Textures
#define UFOT "res/images/SIUFO.png"
#define invaderT1 "res/images/SIInvader1.png" //Crab
#define invaderT2 "res/images/SIInvader2.png" //Octopus
#define invaderT3 "res/images/SIInvader3.png" //Squid
#define shieldT "res/images/SIShield.png"
#define iBulletT "res/images/SIIBullet.png"
#define pBulletT "res/images/SIPBullet.png"
#define playerT "res/images/SIPlayer.png"

//Sound Effects
#define backgroundSE "res/sounds/backgroundSong.wav"
#define UFOSE "res/sounds/ufoSound.wav"
#define invaderKilledSE "res/sounds/invaderKilled.wav"
#define shootingSE "res/sounds/shoot.wav"
#define explosionSE "res/sounds/explosion.wav"

/*--------------COLOR INFO-------------*/
//www.rapidtables.com/web/color/RGB_Color.html
//Black		 = 0, 0, 0
//White		 = 255, 255, 255
//Red		 = 255, 0, 0
//Green		 = 0, 128, 0
//Lime Green = 0, 255, 0
//Dark Green = 0, 100, 0
//Cyan		 = 0, 255, 255
//Dark Cyan  = 0, 139, 139
//Blue		 = 0, 0, 255
//Yellow	 = 255, 255, 0
//Brown		 = 61, 53, 53
//Gray		 = 128, 128, 128
//Navy		 = 0, 0, 128

#endif