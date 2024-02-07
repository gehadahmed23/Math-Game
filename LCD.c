/*
 * LCD.c
 *
 * Created: 11/6/2023 12:52:11 PM
 *  Author: Dell
 */ 
#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>

void LCD_vInit(void)
{
 _delay_ms(200);
 #if defined eight_bits_mode
 DIO_set_port_direction(port, 0xff);
 DIO_vsetPINDir('C',EN,1);
 DIO_vsetPINDir('C',RW,1);
 DIO_vsetPINDir('C',RS,1);
 DIO_write('C',RW,0);
 LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
 _delay_ms(1);
 LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
 _delay_ms(1);
 LCD_vSend_cmd(CLR_SCREEN);//clear the screen
 _delay_ms(10);
 LCD_vSend_cmd(ENTRY_MODE); //entry mode
 _delay_ms(1); 
 
 #elif defined four_bits_mode
 DIO_set_port_direction(port, 0xf0);
  DIO_vsetPINDir('C',EN,1);
  DIO_vsetPINDir('C',RW,1);
  DIO_vsetPINDir('C',RS,1);
  DIO_write('C',RW,0);
 LCD_vSend_cmd(RETURN_HOME); //return home
 _delay_ms(10);
 LCD_vSend_cmd(FOUR_BITS); //4bit mode
 _delay_ms(1);
 LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
 _delay_ms(1);
 LCD_vSend_cmd(CLR_SCREEN);//clear the screen
 _delay_ms(10);
 LCD_vSend_cmd(ENTRY_MODE); //entry mode
 _delay_ms(1);
 #endif
}


static void send_falling_edge(void)
{
 DIO_write('C',EN,1);
 _delay_ms(2);
 DIO_write('C',EN,0);
 _delay_ms(2);
}
void LCD_vSend_cmd(char cmd)
{
 #if defined eight_bits_mode
 DIO_write_port(port,cmd);
 DIO_write('C',RS,0);
 send_falling_edge();
 
 #elif defined four_bits_mode
 write_high_nibble(port,cmd >> 4);
 DIO_write('C',RS,0);
 send_falling_edge();
 write_high_nibble(port,cmd);
 DIO_write('C',RS,0);
 send_falling_edge();
 #endif
 _delay_ms(5);
}

void LCD_vSend_char(char data)
{
 #if defined eight_bits_mode
 DIO_write_port(port,data);
 DIO_write('C',RS,1);
 send_falling_edge();
 
 #elif defined four_bits_mode
 write_high_nibble(port,data >> 4);
 DIO_write('C',RS,1);
 send_falling_edge();
 write_high_nibble(port,data);
 DIO_write('C',RS,1);
 send_falling_edge();
 #endif
 _delay_ms(5);
}


void LCD_vSend_string(char *data)
{
 while((*data)!='\0')
 {
  LCD_vSend_char(*data);
  data++;
 }
}
void LCD_clearscreen()
{
 LCD_vSend_cmd(CLR_SCREEN);
 _delay_ms(10);
}
void LCD_movecursor(char row,char coloumn)
{
 char data ;
 if(row>2||row<1||coloumn>16||coloumn<1)
 {
  data=0x80;
 }
 else if(row==1)
 {
  data=0x80+coloumn-1 ;
 }
 else if (row==2)
 {
  data=0xc0+coloumn-1;
 }
 LCD_vSend_cmd(data);
 _delay_ms(5);
}

void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string.
int LCD_sendfloat(float n, char* res, int afterpoint)
{
	Clear_buffer(res);
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; 
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
	return i;
}
void Clear_buffer(char *res){
	int i = 0;
	while(res[i] != '\0'){
		res[i] = '\0';
		i++;
	}
}	

void LCD_sendFloat(float n, char* res, int afterpoint)
{
	Clear_buffer(res);
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}