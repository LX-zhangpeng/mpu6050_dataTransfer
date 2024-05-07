

/******************************************************************************************/
// * 文件名  ：key.c
// * 描述    ：按键应用函数库     

// * 硬件连接： PA0 - key1     

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/


#include "key.h" 


/******************************************************************************************/
 
/*计数计时，不精确的延时 用于延时去抖动 */  

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/

 
void Key_Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 




/******************************************************************************************/
 
 /*	 配置按键用到的I/O口 */ 

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/



void Key_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //开启按键端口PA的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //端口配置为下拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化端口
}


/******************************************************************************************/
 
 /* 检测是否有按键按下 */

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/


u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*检测是否有按键按下 */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*延时消抖*/
			
	  	Key_Delay(5000);	
			
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*等待按键释放 */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			  else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}

















/******************************************************************************************/

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

/****************************************************************************************/
