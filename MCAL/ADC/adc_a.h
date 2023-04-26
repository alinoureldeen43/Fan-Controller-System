/*
 * adc_a.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Ahmed Hassan
 */

#ifndef MCAL_ADC_ADC_A_H_
#define MCAL_ADC_ADC_A_H_

//#define INTERRUPT_MODE

#ifndef INTERRUPT_MODE
#define POLLING_MODE
#endif

#include"../../LIBRARIES/std_types.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

typedef enum{
	AREF,AVCC,reserved,internal=3
}ADC_Reference;

typedef enum{
	prescaler0,prescaler2,prescaler4,prescaler8,prescaler16,prescale32,prescaler64,prescaler128
}ADC_Prescaler;


typedef struct{
	ADC_Reference reference;
	ADC_Prescaler prescaler;

}ADC_ConfigType;


uint16 ADC_read_Channel(uint8 channel_num);
void ADC_init(ADC_ConfigType *Config_Ptr);

#endif /* MCAL_ADC_ADC_A_H_ */
