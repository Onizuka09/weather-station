/*
 * DHT22.h
 *
 *  Created on: Jan 30, 2023
 *      Author: moktar
 */

#ifndef DHT22_H_
#define DHT22_H_
#include "stdio.h"
#include "stm32f4xx_hal.h"


typedef struct{
	float temperture;
	float  humidity;
}data_t;

void dht22_start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t dht22_begin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
//uint8_t DHT22_Read_byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void get_data(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,data_t *d);
#endif /* DHT22_H_ */
