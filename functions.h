#ifndef Game_Functions_h
#define Game_Functions_h

#include <stdint.h>

//Enemy Size
#define Enemy_w 16
#define Enemy_h 10

//Enemy movement
#define Enemy_vx 1
#define Enemy_vy 1

#define Enemy_x 3
#define Enemy_y 3


//Rows of Enemies
#define MaxRowEnemies 6
#define MinRowEnemies 0

//Coloms
#define num_of_col 4

//Spaceship
#define Spaceship_y

//Bunkers
#define Bunker_w 16
#define Bunker_h 5
#define Bunkers 3
#define Bunker_x Bunker_w
#define Bunker_y
#define Bunkers 3
//Spacers
#define Spacer 2	// Spacer
#define Min_y 0
#define Min_x 0
#define Max_y 159
#define Max_x 127
#define Mid_x (Max_x/2) 
#define Mid_y (Max_y/2) 

// Upper
#define Up_Left_x (Min_x + Spacer) 
#define Up_Left_y (Min_y + Spacer)
#define Up_Right_x (Max_x - Spacer)
#define Up_Right_y (20 + Spacer)

// Lower
#define Low_Left_x (Min_x + Spacer)
#define Low_Left_y (Max_y - Spacer - 20)
#define Low_Right_x (Max_x - Spacer)
#define Low_Right_y (Max_y - Spacer)

// Menu
#define Menu_Left_x (Min_x + Spacer)
#define Menu_Left_y (Min_y + Spacer + 20)
#define Menu_Right_x (Max_x - Spacer)
#define Menu_Right_y (Min_y + Spacer + 20)

// Game Over
#define GameOver_Left_x (Min_x + Spacer)
#define GameOver_Left_y (Min_y + Spacer + 20 + 5 + 55)
#define GameOver_Right_x (Max_x - Spacer)
#define GameOver_Right_y (Min_y - Spacer - 20 - 5)

//Place of Text
#define U 1
#define L 2
#define M 3
#define S 4

//text color
#define BLACK 0x0000
#define WHITE 0xFFFF

//Enemy Rows
#define Level_1_Rows 1
#define Level_1_Enemies 6 
#define Level_2_Rows 2
#define Level_2_Enemies 6
#define Level_3_Rows 3
#define Level_3_Enemies 6 

void Clear(int area);

void Delay_10ms(int delay);



#endif
