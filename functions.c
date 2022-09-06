#include <string.h>

#include "functions.h"
#include "ST7735.h"




void Clear(int area)
{
	int x = 0, y = 0, w = 0, l = 0;
	switch (area)
	{
		case U: // Upper
				x = Up_Left_x;
				y = Up_Left_y;
				w = Up_Right_x;
				l = Up_Right_y;
				break;
		case L: // Lower
				x = Low_Left_x;
				y = Low_Left_y;
				w = Low_Right_x;
				l = Low_Right_y;
				break;
		case M: // Menu
				x = Menu_Left_x;
				y = Menu_Left_y;
				w =  Menu_Right_x;
				l = Menu_Right_y;
				break;
		case S: // Game Over
				x = GameOver_Left_x;
				y = GameOver_Left_y;
				w = GameOver_Right_x;
				l = GameOver_Right_y;

				break;
	}
	ST7735_FillRect(x, y, w, l, BLACK);
}


void Delay_10ms(int delay)
{
	uint32_t volatile time;
  while(delay)
	{
    time = 727240*2/91;  // 10msec
    while(time)
		{
      time--;
    }
    delay--;
  }
}
