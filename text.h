#ifndef text_h
#define text_h

#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdbool.h>

#define Start 1
#define GO 2


void MMenu(void);
void MainMenu(int score, int highscore);
void Ingame(int score, int highscore, int lives, int level);

void Clear_Upper(void);
void Clear_Lower(void);
void Clear_All(void);
void Clear(int area);
void Player_Ship_Clear(void);

void Draw_Text(int x, int y, char *txt, uint16_t color, int size);
void Draw_White_Text(int x, int y, char *txt);

#endif