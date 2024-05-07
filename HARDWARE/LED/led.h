#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1

#define LED_D2   	PCout(13)   // LED_D2---PC13
#define LED_ON     0    //LED低电平 -- 亮
#define LED_OFF    1    //LED高电平 -- 灭

void LED_GPIO_Config(void);
void GPIO_SET_DIRECTIION(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int direction);

#endif /* __LED_H */
					
						
					
					
					
					
					
					
