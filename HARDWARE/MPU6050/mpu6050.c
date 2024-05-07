#include "mpu6050.h"
#include "led.h"
#include "delay.h"

//SDA PB0
//SCL PB1

#define SDA_OUT() GPIO_SET_DIRECTIION(GPIOB,GPIO_Pin_0,1)
#define SDA_IN()  GPIO_SET_DIRECTIION(GPIOB,GPIO_Pin_0,0)

#define IIC_SDA(x)  GPIO_WriteBit(GPIOB,GPIO_Pin_0,x)             
#define IIC_SCL(x)  GPIO_WriteBit(GPIOB,GPIO_Pin_1,x)  

#define READ_SDA  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)


void IIC_Init(void)
{
	   GPIO_SET_DIRECTIION(GPIOB,GPIO_Pin_0,1);  //SDA=output
	   GPIO_SET_DIRECTIION(GPIOB,GPIO_Pin_1,1);  //SCL=output

     GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);  //SDA=1
     GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);  //SCL=1
}

void IIC_Start(void)
{
     SDA_OUT();
     IIC_SDA(Bit_SET);
     IIC_SCL(Bit_SET);
     delay_us(4);
     IIC_SDA(Bit_RESET);
     delay_us(4);
     IIC_SCL(Bit_RESET);
}

void IIC_Stop(void)
{
     SDA_OUT();
     IIC_SCL(Bit_RESET);
     IIC_SDA(Bit_RESET);
     delay_us(4);
     IIC_SCL(Bit_SET);
     delay_us(4);
     IIC_SDA(Bit_SET);
}

unsigned char IIC_Wait_Ack(void)
{
     unsigned char ucErrTime=0;
     SDA_IN();
     IIC_SDA(Bit_SET);  delay_us(1);
     IIC_SCL(Bit_SET);  delay_us(1);
     SDA_IN();
     while(READ_SDA)
     {
          ucErrTime++;
          if(ucErrTime>250)
          {
               IIC_Stop();
               return 1;
          }
     }
     IIC_SCL(Bit_RESET);
     return 0;
}

void IIC_Ack(void)
{
     IIC_SCL(Bit_RESET);
     SDA_OUT();
     IIC_SDA(Bit_RESET);
     delay_us(2);
     IIC_SCL(Bit_SET);
     delay_us(2);
     IIC_SCL(Bit_RESET);
}

void IIC_NAck(void)
{
     IIC_SCL(Bit_RESET);
     SDA_OUT();
     IIC_SDA(Bit_SET);
     delay_us(2);
     IIC_SCL(Bit_SET);
     delay_us(2);
     IIC_SCL(Bit_RESET);
}

void IIC_Send_Byte(unsigned char txd)
{
     unsigned char t;
     SDA_OUT();
     IIC_SCL(Bit_RESET);
     for(t=0;t<8;t++)
     {
          IIC_SDA((txd&0x80)>>7);
          txd<<=1;
          delay_us(2);
          IIC_SCL(Bit_SET);
          delay_us(2);
          IIC_SCL(Bit_RESET);
          delay_us(2);
     }
}

unsigned char IIC_Read_Byte(unsigned char ack)
{
     unsigned char i,receive=0;
     SDA_IN();
     for(i=0;i<8;i++)
     {
        IIC_SCL(Bit_RESET);
        delay_us(2);
        IIC_SCL(Bit_SET);
        receive<<=1;
        SDA_IN();
        if(READ_SDA) receive++;
        delay_us(1);
     }
     if(!ack)
       IIC_NAck();
     else
       IIC_Ack();
     return receive;
}

#define MPU6050_ADDR       0x6B      //AD0 = 0 Ê±µØÖ·
#define CONFIG             0x1a
#define GYRO_CONFIG        0x1b
#define ACCEL_CONFIG       0x1c	
#define INT_PIN_CFG        0x37 
#define MPU6050_BURST_ADDR 0x3b 
#define USER_CTLR          0x6a	       
#define PWR_MGMT1          0x6b	     
#define PWR_MGMT2          0x6c
#define MPU6050_ID_ADDR	   0x75
#define MPU6050_ID	       0x68 


void MPU6050_Init()
{
	  unsigned char data_buf = 0;
	
    MPU6050_write(0x6B,0x80);
    delay_us(100);
    MPU6050_write(0x6B,0x00);
    
    /* iic bypass en */
    data_buf = 0x02;
    MPU6050_write(INT_PIN_CFG,data_buf);
  
    /* iic master disable */
    data_buf  =0x00;
    MPU6050_write(USER_CTLR,data_buf);

    /* mpu6050 sleep disable, temperature en, in 8M osc */
    data_buf = 0x00;
    MPU6050_write(PWR_MGMT1,data_buf);

    /* mpu6050 no standby mode */
    data_buf = 0x00;
    MPU6050_write(PWR_MGMT2,data_buf);

    /* DLPF */
    data_buf = 0x06;
    MPU6050_write(CONFIG,data_buf);

    /* GYRO +-2000 ¡ã/s */  
    data_buf = 0x18;
    MPU6050_write(GYRO_CONFIG,data_buf);
  
    /* ACC +-4g */
    data_buf = 0x08;
    MPU6050_write(ACCEL_CONFIG,data_buf);
}

void MPU6050_write(unsigned char addr,unsigned char data)
{
    IIC_Start();
    IIC_Send_Byte(0x68<<1);
    IIC_Wait_Ack();

    IIC_Send_Byte(addr);
    IIC_Wait_Ack();

    IIC_Send_Byte(data);
    IIC_Wait_Ack();

    IIC_Stop();
}

void MPU6050_Read(unsigned char addr,unsigned char *data)
{    
    IIC_Start();
    IIC_Send_Byte(0x68<<1);
    IIC_Wait_Ack();

    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    IIC_Start();

    IIC_Send_Byte((0x68<<1)|0x01);
    IIC_Wait_Ack();
    *data=IIC_Read_Byte(0);
    IIC_Stop();
}

