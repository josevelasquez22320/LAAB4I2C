//******************************************************************************************************************
//UNIVERSIDAD DEL VALLE DE GUATEMALA
//IE3054: Electrónica Digital 2
//Archivo: Clase_I2C_Esclavo
//AUTOR: Jose Andrés Velásquez García 
//Clase I2C
//HARDWARE: ATMEGA328P
//CREADO: 12/02/2025
//ÚLTIMA MODIFICACIÓN: 12/02/2025 - 16:17
//******************************************************************************************************************
#define F_CPU 16000000		// Definir CPU con el que trabajara el microcontrolador
#include <avr/io.h>			// Se incluye la libreria para poder utilizar los puertos del microcontrolador
#include <util/delay.h>		// Se incluye la libreria que implementa los delay
#include <avr/interrupt.h>	//Se incluye las librerias de las interrupciones


//Se incluyen las Librerias Propias
#include "I2C/I2C.h"
#include "ADC/ADC.h"
//Se define la dirreción de la comunicación (Maesro a Esclavo)
#define SlaveAddress 0x30

//Se definen los prototipos de función

void init_setup(void);		//Prototipo de función para inicializar los puertos
void refreshPORT(uint8_t valor);	//Prototipo de función para las salidas
void ADC_init(void);			//Prototipo de función para inicializar la ADC

uint16_t ADC_read(uint8_t canal);		//Prototipo de función para leer los canales del ADC


//******************************************************************************************************************
//VARIABLES GLOBALES
//******************************************************************************************************************
uint8_t buffer = 0;
volatile uint8_t valorADC = 0;

//******************************************************************************************************************
//LOOP
//******************************************************************************************************************

int main(void)
{
	DDRB |=(1 << DDB5);
	PORTB &= ~(1 << PORTB5);
	ADC_init();

	I2C_Slave_Init(SlaveAddress);		//Se inicia el esclavo con la dirección del maestro designada

	sei();		// Habilitar Interrupciones generales

 
    while (1) 
    {

		// Iniciando secuencia de adc
		valorADC = ADC_read(0);
		if(buffer == 'R'){
			PINB |= (1 << PINB5);
			buffer = 0;
		}
	
	}
}


//******************************************************************************************************************
//FUNCIONES
//******************************************************************************************************************
/*

void init_setup(void){
	// Salidas
	DDRC |=(1 << DDC1)|(1 << DDC2)|(1 << DDC3);
	DDRD |=(1 << DDD2)|(1 << DDD3)|(1 << DDD4)|(1 << DDD5)|(1 << DDD6);
	refreshPORT(0);
	DDRB |=(1 << DDB5);
}


void refreshPORT(uint8_t valor){
	if(valor & 0b10000000){
		PORTD |=(1 << PORTD6);
		}else{
		PORTD &= ~(1 << PORTD6);
	}
	if(valor & 0b01000000){
		PORTD |=(1 << PORTD5);
		}else{
		PORTD &= ~(1 << PORTD5);
	}
	if(valor & 0b00100000){
		PORTD |= (1 << PORTD4);
		}else{
		PORTD &= ~(1 << PORTD4);
	}
	if(valor & 0b00010000){
		PORTD |= (1 << PORTD3);
		}else{
		PORTD &= ~(1 << PORTD3);
	}
	if(valor & 0b00001000){
		PORTD |= (1 << PORTC2);
		}else{
		PORTD &= ~(1 << PORTC2);
	}
	if(valor & 0b00000100){
		PORTC |= (1 << PORTC3);
		}else{
		PORTC &= ~(1 << PORTC3);
	}
	if(valor & 0b00000010){
		PORTC |= (1 << PORTC2);
		}else{
		PORTC &= ~(1 << PORTC2);
	}*/
/*
	if(valor & 0b00000001){
		PORTC |= (1 << PORTC1);
		}else{
		PORTC &= ~(1 << PORTC1);
	}
	
}
*/



//******************************************************************************************************************
//INTERRUPCIONES
//******************************************************************************************************************

ISR(ADC_vect){
	ADCSRA |= (1 << ADIF);	//Limpiar la bandera al encender el ADC
}


ISR(TWI_vect){
	uint8_t estado;
	estado = TWSR & 0xFC;
	switch(estado){
		case 0x60:
		case 0x70:
		TWCR |=(1 << TWINT);
		break;
		case 0x80:
		case 0x90:
		buffer = TWDR;
		TWCR |= (1 << TWINT); // Se limpia la bandera
		break;
		case 0xA8:
		case 0xB8:
		TWDR = valorADC; // Cargar el dato
		TWCR = (1 << TWEN)|(1 << TWIE)|(1 << TWINT)|(1 << TWEA); // Inicia el envio
		break;
		default: // Se libera el bus de cualquier error
		TWCR |=(1 << TWINT)|(1 << TWSTO);
		break;
	}
}
		
