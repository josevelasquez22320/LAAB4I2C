/*
 * I2C.h
 *
 * Created: 18/02/2025 18:18:58
 *  Author: josea
 */ 


#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


#define E (1 << PORTB3)			//Se puede definir un puerto como una letra
//para mayor facilidad al momento de programar

#define RS (1 << PORTB2)

//Funcion para inicializar LCD en modo 4 bits
void initLCD8bits(void);
// Funcion para colocar en el puerto un valor
void LCD_Port(char a);
// Funcion para enviar un comando
void LCD_CMD(char a);
// Funcion para enviar un caracter
void LCD_Write_Char(char c);
// Funcion para enviar una cadena
void LCD_Write_String(char *a);
// Desplazamiento hacia la derecha
void LCD_Shift_Right(void);
// Desplazamiento hacia la izquierda
void LCD_Shift_Left(void);
// Establecer el cursor
void LCD_Set_Cursor(char c, char f);

void LCD_Clear(void);






#endif /* I2C_H_ */