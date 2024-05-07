#include "led.h"

 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 	// 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;							// 选择对应的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // 上拉输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  								// 初始化PC端口
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 										// 关闭所有LED
}

void GPIO_SET_DIRECTIION(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int direction)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	// 使能PB端口时钟 

  if(direction == 1)
	{
		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin;					// 引脚
	  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_Out_OD;	// 开漏输出模式
	  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;	// 高速模式
	  GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
	else
	{
		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin;					// 引脚
	  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;	// 输入模式
	  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;	// 高速模式
	  GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
}

