#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdint.h>
#include "functions.h"

typedef enum {dead, alive} status_t;

struct sprite{
		int32_t x;	// x coordinate
		int32_t y;	// y coordinate
		int32_t vx, vy;	// velocity. pixels/ 30 Hz
		const unsigned short *image[2];	// ptr -> image. Need 2 images to implement animation for a sprite.
		const unsigned short *black;	// ptr -> black image to cover up the image when sprite is dead.
		status_t life;	// dead/alive
		uint32_t w;	// width
		uint32_t h;	// height
		uint32_t needDraw;	// Semaphore
		uint32_t hits; //number of enemies
		uint32_t points;
		uint32_t im_ch;
};

extern int score;
extern int highscore;
extern int lives;
extern int level;
extern int Flag;
extern int Anyalive;
extern int game_fin;
extern int status;
extern int clear_ship;

typedef struct sprite sprite_t;
typedef struct sprite Laser1_t;
typedef struct sprite spaceship_t;
typedef struct sprite missile_t;
typedef struct sprite enemy_t;
typedef struct sprite bunker_t;
		
	// player sprites
extern spaceship_t SpaceShip;
extern Laser1_t Laser;
extern bunker_t Bunker[Bunkers];
extern missile_t Missile;
extern enemy_t Enemy [Level_3_Rows][Level_3_Enemies];
#endif
