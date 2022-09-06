
#include "Button.h"
#include "variable.h"



void Button_Init(void)
{
	// Enable PORTE
	SYSCTL_RCGCGPIO_R |= E;    
	while((SYSCTL_PRGPIO_R & E) == 0){};
	
	// SW: PE0
	GPIO_PORTE_DIR_R &= ~PE0;
	GPIO_PORTE_DEN_R |= PE0;	
	GPIO_PORTE_PUR_R |= PE0;
	}

//shoot
void Shoot(void)
	{
	Laser.x = Laser.x + Laser.w/2;
	Laser.y = Laser.y;
	Laser.life = alive;
	Laser.needDraw = 1;
}
	
// shoot on button
bool Shoot_SW(void)
{
	return !(GPIO_PORTE_DATA_R&PE0);
}
	