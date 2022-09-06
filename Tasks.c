

#include "tasks.h"
#include "tm4c123gh6pm.h"
#include "Slide.h"
#include "variable.h"
#include "Button.h"
#include "random.h"
#include "functions.h"



bunker_t Bunker[Bunkers];

unsigned long FR_30_HZ = 2664000+750000;
unsigned long FR_60_HZ = 1332000;


void Game_Task_Init(void)
{
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = FR_30_HZ-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = 0x07;
  EnableInterrupts();	// make I = 0
}


// Scoring
int score = 0;
int highscore = 0;
//Number Of Lives
int lives = 3;
//Level Number
int level = 1;
//Enemy Count
int enemy_Count = 0;
int i_bound = 0;
int j_bound = 0;
// Semaphores
int Flag;	
int Anyalive;	
int game_fin = 0;
int status = 0;

int clear_player_ship = 1;







void SysTick_Handler(void)
{
	
//Tasks
	//Set Size
	Level_Size();
	//Keep track of number of enemies
	Enemy_Count();
	
	//Hit detection
	Hit_Detection();
	
	// Move Sprites
	Game_Move();

	//Shoot weapons
	Shoot_Enemy();
	
	
	Hit_Detection();
	
	
	game_fin = 1;
	
}

void Game_Move(void)
{
	

	
	// shoot laser based on input
	bool SW_Pressed = Shoot_SW();
	
	if (SW_Pressed && Laser.life == dead)
	{
		Shoot_Laser();
	}
	
	//Move Player laser
	if(Laser.life == alive)
	{
		Laser.needDraw = 1;

		if(Laser.y < Up_Right_y + Laser.h)
			Laser.life = dead;
		
		Laser.y += Laser.vy;
	}
		

	if (Missile.life == alive)
	{
		Missile.needDraw = 1;
		Anyalive = 1;
		
		if (Missile.y > Low_Right_y + Missile.h)
			Missile.life = dead;
		
		Missile.y += Missile.vy;
		
	}
		
	//Move enemies
	for (int i = 0; i < i_bound; i++)
	{
		
		for (int j = 0; j < j_bound; j++)
		{
			
	
				Enemy[i][j].needDraw = 1;
				Anyalive = 1;
				
				if((Enemy[i][j].y > 119) || (Enemy[i][j].y < Up_Left_y)){
					status = 2;
				}		
				
				if((Enemy[i][j].x < Min_x) || (Enemy[i][j].x > Max_x-Enemy[i][j].w)){

					for (int p = 0; p < j_bound; p++)
					{
						Enemy[i][j].y += Enemy[i][j].vy;
						Enemy[i][j].vx = -1*Enemy[i][j].vx;
					}
					
					if (j == j_bound-1)
					{
							for (int p = 0; p < j_bound-1; p++)
							{
								Enemy[i][p].x += 2*Enemy[i][p].vx;
							}
					}
				}
				Enemy[i][j].x += Enemy[i][j].vx;	 
		}
	}
	
}
void Shoot_Laser(void)
{
	// update laser to front of player ship
	Laser.x = SpaceShip.x + SpaceShip.w/2;
	Laser.y = SpaceShip.y;
	Laser.life = alive;
	Laser.needDraw = 1;
}

void Level_Size(void)
{
	switch (level)
		{
			case 1:
				i_bound = Level_1_Rows;
				j_bound = Level_1_Enemies;
				break;
			case 2:
				i_bound = Level_2_Rows;
				j_bound = Level_2_Enemies;
				break;
			default:
				i_bound = Level_3_Rows;
				j_bound = Level_3_Enemies;
				break;
		}
}

void Enemy_Count(void)
{
	enemy_Count = 0;
	for (int i = 0; i < i_bound; i++)
		for(int j = 0; j < j_bound; j++)
			if (Enemy[i][j].life == dead)
				enemy_Count++;
			
	if (enemy_Count == i_bound*j_bound)
	{
		status = 3;
	}
}

void Shoot_Enemy(void)
{ 
	if (enemy_Count == i_bound*j_bound)
		return;
	
	if (Laser.life == dead || Missile.life == dead)
	{
		int i = i_bound-1;
		int j = Random32() % j_bound;	
		while (Enemy[i][j].life != alive)
		{
			if (i > 0)
				i--;
			else
			{
				i = i_bound-1;
				j = Random32() % j_bound;
			}
		}
		
		int weapon_x = Enemy[i][j].x + 16/2;
		int weapon_y = Enemy[i][j].y + 10;
		
		if (Laser.life == dead)
		{
			Laser.x = weapon_x;
		Laser.y = weapon_y;
			Laser.life = alive;
			Laser.needDraw = 1;
		}	
		else if (Missile.life == dead)
		{
			Missile.x = weapon_x;
		Missile.y = weapon_y;
			Missile.life = alive;
			Missile.needDraw = 1;
		}	
	}
}

void Hit_Detection(void)
{
	//Hit detects when Laser hits enemy
	if (Laser.life == alive)
	{
		int sx0 = Laser.x;
		int sy0 = Laser.y;
		int sw = Laser.w;
		int sx1 = sx0 + sw;
	
		
		int i = i_bound-1;
		
		for (int j = 0; j < j_bound; j++)
		{
			while (Enemy[i][j].life != alive)
			{
				if (i > 0)
					i--;
				else
					break;
			}
			
			enemy_t n_enemy = Enemy[i][j];
			
			int ex0 = n_enemy.x;
			int ey0 = n_enemy.y;
			int ew  = n_enemy.w;
			int eh  = n_enemy.h;
			int ex1 = ex0 + ew;
			int ey1 = ey0 + eh;
			
			if ((ex0 <= sx0) && (ex1 >= sx1 ))
			{
				if (ey1 >= sy0)
				{
					if (Enemy[i][j].hits < 1)
					{
						score += Enemy[i][j].points;
						Laser.life = dead;
						Enemy[i][j].life = dead;
						Enemy[i][j].hits++;
						Enemy[i][j].im_ch = 1;
					}
				}
			}
		}		
		if (sy0 <= Up_Right_y)
		{
			Laser.life = dead;
		}	
	}
	
	//Hit detect htting bunker and player ship
	if (Laser.life == alive || Missile.life == alive)
	{
		int laser_x0, laser_y0, laser_x1, laser_y1;
		int missile_x0, missile_y0, missile_x1, missile_y1;
		
		
		if (Laser.life == alive)
		{
			laser_x0 = Laser.x;
			laser_y0 = Laser.y;
			laser_x1 = laser_x0 + Laser.w;
			laser_y1 = laser_y0 + Laser.h;
		}
		
		if (Missile.life == alive)
		{
			missile_x0 = Missile.x;
			missile_y0 = Missile.y;
			missile_x1 = missile_x0 + Missile.w;
			missile_y1 = missile_y0 + Missile.h;
		}
		
		
		for (int b = 0; b < Bunkers; b++)
		{
			bunker_t bunker = Bunker[b];
			if (bunker.life == alive)
			{
				if (((bunker.x <= laser_x0) && (bunker.x+bunker.w >= laser_x1)))
				{
					if ((bunker.y+bunker.h <= laser_y1))
					{
						if (Bunker[b].hits < 2)
						{
								Laser.life = dead;
								Bunker[b].hits++;
								Bunker[b].im_ch = 1;
						}
						else
						{
							Bunker[b].life = dead;				
						}
					}
				}
				
			}
		}
		for (int b = 0; b < Bunkers; b++)
		{
			bunker_t bunker = Bunker[b];
			if (bunker.life == alive)
			{
				if (((bunker.x <= missile_x0) && (bunker.x+bunker.w >= missile_x1)))
				{
					if ((bunker.y+bunker.h <= missile_y1))
					{
						if (Bunker[b].hits < 2)
						{
								Missile.life = dead;
								Bunker[b].hits++;
								Bunker[b].im_ch = 1;								
						}
						else
						{
							Bunker[b].life = dead;
						}
					}
				}				
			}
		}		
		if (SpaceShip.life == alive)
		{
			if ((SpaceShip.x <= missile_x0) && (SpaceShip.x+SpaceShip.w >= missile_x1))
			{
				if (SpaceShip.y+SpaceShip.h <= missile_y1)
				{					
					if (lives == 1)
						status = 2;					
					if (lives > 1)
						lives--;					
					New_SpaceShip();		
				}
			}			
			if ((SpaceShip.x <= laser_x0) && (SpaceShip.x+SpaceShip.w >= laser_x1))
			{
				if (SpaceShip.y+SpaceShip.h <= laser_y1)
				{
					if (lives == 1)
						status = 2;					
					if (lives > 1)
						lives--;
					New_SpaceShip();	
				}
			}
		}
		if (missile_y1 >= 134+SpaceShip.h)
		{
			Missile.life = dead;
		}
		
		if (laser_y1 >= 134+SpaceShip.h)
		{
			Laser.life = dead;
		}
	}	
}

void New_SpaceShip(void)
{
	clear_player_ship = 1;
}










