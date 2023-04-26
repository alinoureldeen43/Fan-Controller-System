/*
 * adc.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Ali Hassan
 */
#include "adc_a.h"

#include<avr/io.h>

#include "../../LIBRARIES/common_macros.h"
#include "../GPIO/gpio_a.h"


void ADC_init(ADC_ConfigType *Config_Ptr)
{
	/* choose volt reference */
	ADMUX= ((Config_Ptr->reference)<<6);

	/* ADC ENABLE SET ADEN BIT*/
	ADCSRA=(1<<ADEN);

	/* IF INTERRUPT MODE ON THEN SET ADIE BIT */
#ifdef INTERRUPT_MODE
	SET_BIT(ADCSRA,<ADIE);
#endif

	/* ADC CHOOSE CLOCK */
	SET_BIT(ADCSRA,Config_Ptr->prescaler);
}

#ifdef INTERRUPT_MODE
void ADC_read_Channel(uint8 channel_num)
{
	/*INSERT CHANNEL NUMBER IN BIT */
	ADMUX = (ADMUX&0xE0) | channel_num;

	/* START CONVERSION BIT SET */
	SET_BIT(ADCSRA,ADSC);
}
#endif

#ifndef INTERRUPT_MODE
#ifdef POLLING_MODE
uint16 ADC_read_Channel(uint8 channel_num)
{
	/*INSERT CHANNEL NUMBER IN BIT */
	ADMUX = (ADMUX&0xE0) | (channel_num&0x07);

	/* START CONVERSION BIT SET */
	SET_BIT(ADCSRA,ADSC);

	/* POLING UNITLL ADC FLAG SET*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	/* CLEAR ADC INTERRUPT FLAG BY SET BIT*/
	SET_BIT(ADCSRA,ADIF);

	/* RETURN DATA REGISTER */
	return ADC;
}
#endif
#endif
