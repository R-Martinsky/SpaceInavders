#ifndef TASKS_H
#define TASKS_H


void Game_Task_Init(void);
void Game_Move(void);
void Shoot(void);
void Shoot_Laser(void);
void Shoot_Enemy(void);
void New_SpaceShip(void);
void ADC0_InSeq3(void);
void Slide_init(void);
void Slide_update(void);
void Hit_Detection(void);
void Enemy_Count(void);
void Level_Size(void);
void Menu_Clear(void);
void SubMenu_Clear(void);
void Player_Ship_Clear(void);
void Menu(int style);
void GO_Menu(void);




void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


#endif
