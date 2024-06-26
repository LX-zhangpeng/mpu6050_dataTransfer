#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"


/******************************************************************************************/
//STM32F103 开发板

//// *按键按下标置
//// KEY_ON 0
//// KEY_OFF 1

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/


#define KEY_ON	1
#define KEY_OFF	0

void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif 






/******************************************************************************************/
//STM32F103 开发板

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/






