/*
 * ADC.c
 *
 * Created: 2/13/2025 7:14:34 PM
 *  Author: JOSEA
 */ 
#include "ADC.h"
#include <avr/io.h>
//Configuración del ADC

void ADC_init(void) {
	ADMUX |= (1<<REFS0);	//Seleccionar el voltaje de referencia
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<ADLAR);	// Se define que se trabajara con 10 bits
	
	// Configuración Prescaler de 128 --> 16M/128 = 125KHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRA |= (1<<ADEN);	// Se enceinde el ADC y se activa su interruptor de igual forma
	
	//Entradas para los potenciometros
	DIDR0 |= (1 << ADC0D);		// Desabilitar la entrada digital PC0
}

uint16_t ADC_read(uint8_t canal){
	ADMUX = (ADMUX & 0xF0)|canal;			//Seleccionar el canal del ADC
	ADCSRA |= (1<<ADSC);					// Se inicia la conversión de lo valores
	while((ADCSRA)&(1<<ADSC));				//Se espera hasta que la conversión se haya completado
	return(ADC);							//Regresa el valor de ADC
}

