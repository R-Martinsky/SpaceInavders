#include "text.h"
#include "functions.h"
#include "tasks.h"
#include "ST7735.h"
#include "variable.h"

// Draw Text
void Draw_Text(int x, int y, char *txt, uint16_t color, int size)
{
	for (int i = 0; i < strlen(txt); i++)
	{
		ST7735_DrawCharS(x, y, txt[i], color, BLACK, size);
		x += 6*size;
	}
}

//Draw White Text
void Draw_White_Text(int x, int y, char *txt)
{
	Draw_Text(x, y, txt, WHITE, 1);
}

// Delay
void DelayWait10ms(uint32_t n){uint32_t volatile time;
  while(n){
    time = 727240*2/91;  // 10msec
    while(time){
      time--;
    }
    n--;
  }
}

// Menus
void Menu(int style)
{
	switch(style)
	{
		case Start:
			MMenu();
				break;
		case GO:
			GO_Menu();
			break;
	}
}

//MainMenu
void MMenu(void)
{

	char start_txt1[] = "PLAY  ";
	char start_txt2[] = "SPACE INVADERS";
	char start_txt3[] = "(Hold to start)";
	
	int x = Mid_x - (strlen(start_txt1)*5)/2;
	int y = 27 + 10;
	
	x = Mid_x - (strlen(start_txt2)*5)/2;
	y = 27 + 3*10;
	
	
	x = Mid_x - (strlen(start_txt2)*6)/2;
	y = 27 + 6*10;
	
	Draw_White_Text(x, y, start_txt3);

}	

//Main Menu boarders
void MainMenu(int score, int highscore)
{
	char score_txt[] 	= "Score  Hi-Score ";

	int x = Mid_x - (strlen(score_txt)*6)/2;
	int y = Up_Left_y;
	
	

		char score_val[4];
		sprintf(score_val, "%d", score);
	
		y = Up_Left_y + 10;
		x = 6;
	
	
	
		char highscore_val[4];
		sprintf(highscore_val, "%d", highscore);
		
		y = Up_Left_y + 10;
		x = 6*9;
		
	
}
// Text in game boarders
void Ingame(int score, int highscore, int lives, int level)
{

	MainMenu(score, highscore);
	
	char live_val[1];
	sprintf(live_val, "%d", lives);
	
	int x = Low_Left_x;
	int y = Low_Left_y + 13;
	

	
	x = Low_Left_x + 6;
	y = Low_Left_y + 19;
	
	
	char level_val[4];
	sprintf(level_val, "%d", level);
	
	x = Low_Right_x-6*strlen(level_val);
	y = Low_Left_y + 13;
	
	
}

// Clear spaceship
void Player_Ship_Clear(void)
{
	ST7735_FillRect(Min_x, SpaceShip.y-SpaceShip.h+1, Max_x, SpaceShip.h, BLACK);
}

// Game Over menu
void GO_Menu(void)
{
	
	Menu_Clear();
	SubMenu_Clear();
	
	char gameover_txt1[] = "GAME OVER";
	char gameover_txt2[] = "(Shoot to Start)";
	
	int x = Mid_x - (strlen(gameover_txt1)*6)/2;
	int y = 27 + 3*10;
	
	Draw_Text(x, y, gameover_txt1, WHITE, 1);
	
	x = Mid_x - (strlen(gameover_txt2)*6)/2;
	y = 27 + 6*10;
	
	Draw_Text(x, y, gameover_txt2, WHITE, 1);
	
}

// Clear menu
void Menu_Clear(void)
{
	Clear(M);
}

// Clear GO menu
void SubMenu_Clear(void)
{
	Clear(S);
}


// Clear Upper Boarder
void Clear_Upper(void)
{
	Clear(1);
}

// Clear Lower Boarder
void Clear_Lower(void)
{
	Clear(2);
}

// Clear all Boarders
void Clear_All(void)
{
	Clear(1);
	Clear(2);
}
