#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "mpu6050.h"
 
int main(void)
{	
	char str_mon[20];
	int fan_date;
  int fan_year;
	
	unsigned char dev_id = 0;
	unsigned char accel[6];
	short int accel_x=0;
	short int accel_y=0;
	short int accel_z=0;
	double degree_x=0;
	double degree_y=0;
	
	int format_x=0;
	int format_y=0;
	int format_z=0;
	
	delay_init();	     //延时函数初始化	 
	delay_ms(3000);
	
	LED_GPIO_Config(); //LED 端口初始化 
	uart_init(19200);	 //串口初始化为19200
	IIC_Init();        //初始化IIC相关
	MPU6050_Init();
	
	delay_ms(1000);
  
	printf("hello,it's nice day!\r\n");

	sscanf(__DATE__,"%s %x %x",str_mon,&fan_date,&fan_year);
	printf("date:%x %s %x\r\n",fan_date,str_mon,fan_year);
	
  MPU6050_Read(0x75,&dev_id);
  printf("device id is %x\r\n",dev_id);
	
	while(1)
	{
		delay_ms(200);
		LED_D2 = !LED_D2;
		
		MPU6050_Read(0x3b,&accel[0]);
		MPU6050_Read(0x3c,&accel[1]);
		MPU6050_Read(0x3d,&accel[2]);
		MPU6050_Read(0x3e,&accel[3]);
		MPU6050_Read(0x3f,&accel[4]);
		MPU6050_Read(0x40,&accel[5]);
		
		accel_x = accel[0]<<8|accel[1];
		accel_y = accel[2]<<8|accel[3]; 
		accel_z = accel[4]<<8|accel[5];
		
		degree_x = atan(accel_x * 1.0f / (accel_z-1900)) * 180.0/3.14;
		degree_y = atan(accel_y * 1.0f / (accel_z-1900)) * 180.0/3.14;
		
		
		//按一定格式化数据，最高位为1则是负数，最高位为0是正数
		format_x = (int)degree_x;
		format_x = format_x >0?format_x:(format_x*-1 + 1000);
		
	  format_y = (int)degree_y;
		format_y = format_y >0?format_y:(format_y*-1 + 1000);
		
		format_z = 0;
		
		
		//printf("acc_x is %d,acc_y is %d,acc_z is %d\r\n\r\n",accel_x,accel_y,accel_z);
		printf("sx:%04dy:%04dz:%04de",format_x,format_y,format_z);
	}

}
