/*
 * DHT22.c
 *
 *  Created on: Jan 30, 2023
 *      Author: moktar
 */


#include "DHT22.h"

extern TIM_HandleTypeDef htim1;



void Delay_us(uint16_t time){
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while (__HAL_TIM_GET_COUNTER(&htim1)<time)
	{

	}
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void dht22_start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	Set_Pin_Output(GPIOx, GPIO_Pin);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 0);
	Delay_us(1200);//wait for > 1ms
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin,1);
	Delay_us(30);
	Set_Pin_Input(GPIOx, GPIO_Pin);


}
uint8_t dht22_begin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	uint8_t res = 0 ;
	Delay_us(40);
	if ( !(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))){
		// if its not 1
		Delay_us(80);
		if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)){
			res= 1 ;
		}
		else {
			res = -1;
		}
	}
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
	//printf("bgin done \n");
	// wait to go low
return res ;
}

static uint8_t DHT22_Read_byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	uint8_t i=0,j;
	for (j=0;j<8;j++){

		while (!(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)));// it's not low
		Delay_us(40);
		if(!( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)))
		{
			i &= ~(1<<(7-j));
		}
		else {
			i |= (1<<(7-j));
		}
		while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));

	}
	//printf("read done \n");
	return i ;

}
void get_data(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,data_t *d){
	uint16_t Hum,Temp,sum;
	uint8_t hum_Byte1,hum_Byte2;
	uint8_t tem_Byte1,temp_Byte2;
	  hum_Byte1= DHT22_Read_byte(GPIOx, GPIO_Pin);
		 // printf("hum_Byte1: %u\n",hum_Byte1);
	 hum_Byte2=DHT22_Read_byte(GPIOx, GPIO_Pin);
		 // printf("hum_Byte2: %u\n",hum_Byte2);
		  tem_Byte1=DHT22_Read_byte(GPIOx, GPIO_Pin);
		 // printf("temp_Byte1: %u\n",tem_Byte1);
		  temp_Byte2=DHT22_Read_byte(GPIOx, GPIO_Pin);
		 // printf("temp_Byte2: %u\n",temp_Byte2);
		  sum=DHT22_Read_byte(GPIOx, GPIO_Pin);
		 // printf("sum: %u\n",sum);
		 // if (sum == (hum_Byte1+hum_Byte2+tem_Byte1+temp_Byte2)){
			  Temp= ((tem_Byte1<<8)|temp_Byte2);
			  Hum = ((hum_Byte1<<8)|hum_Byte2);
		 //}
		  d->temperture = (float) (Temp/10.0);
		  d->humidity = (float) (Hum/10.0) ;

}


