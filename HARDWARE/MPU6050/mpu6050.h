#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <math.h>
#include <stdio.h>

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(unsigned char txd);
unsigned char IIC_Read_Byte(unsigned char ack);

void MPU6050_Init(void);
void MPU6050_write(unsigned char addr,unsigned char data);
void MPU6050_Read(unsigned char addr,unsigned char *data);
      
#endif
