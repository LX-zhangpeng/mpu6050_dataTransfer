#include "led.h"

 /***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 	// ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;							// ѡ���Ӧ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  								// ��ʼ��PC�˿�
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 										// �ر�����LED
}

void GPIO_SET_DIRECTIION(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int direction)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	// ʹ��PB�˿�ʱ�� 

  if(direction == 1)
	{
		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin;					// ����
	  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_Out_OD;	// ��©���ģʽ
	  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;	// ����ģʽ
	  GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
	else
	{
		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin;					// ����
	  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;	// ����ģʽ
	  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;	// ����ģʽ
	  GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
}

