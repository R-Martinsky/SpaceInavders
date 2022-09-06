#ifndef Button_h
#define Button_h

#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdbool.h>
#include "SysTick.h"

#define E 0x10
#define PE0 0x01


void Button_Init(void);

void Button_Update(void);

void Shoot(void);

bool Shoot_SW(void);
#endif
