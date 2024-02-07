/*
 * Gehad_Ahmed.c
 *
 * Created: 11/6/2023 12:52:11 PM
 *  Author: Dell
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "keypad_driver.h"
#include "LCD.h"
#include "LED.h"
#include "Timer.h"
#include <math.h>
#include <stdio.h>
int unsigned counter1 = 0, counter2 = 0, counter3 = 0, level = 0;
int main(void)
{
   timer_CTC_init_interrupt();
   LCD_vInit();
   keypad_vInit();
   long long num1, num2, num3, num4;
   double result;
   char anser;
   char flagNegative = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, x = NOTPRESSED;
   char operation[] = {'-', '+', '*', '/'};
   label:
   LCD_movecursor(1, 2);
   LCD_vSend_string("Welcome to the");
   LCD_movecursor(2, 4);
   LCD_vSend_string("math game");
   _delay_ms(2000);
   LCD_clearscreen();
   LCD_movecursor(1, 4);
   LCD_vSend_string("Level ");
   LCD_vSend_char(++level + '0');
   _delay_ms(1500);
   LCD_clearscreen();
   counter1 = 0;
   while (1)
   {
	   
	   if(flag1 == 0){
		   flag1 = 1;
		   num1 = (rand() % (100 - 1 + 1)) + 1; // Randomly choose the first number
		   num2 = (rand() % (100 - 1 + 1)) + 1; // Randomly choose the second number
		   char op = rand() % 4; // choose random operation
		   if(operation[op] == '+'){
			   result = num1 + num2;
		   }
		   else if(operation[op] == '-'){
			   result = num1 - num2;
			   if(num1 < num2){
			     flagNegative = 1;
				 result *= (-1);
			   }			   
		   }
		   else if(operation[op] == '/'){
			   double a = num1, b = num2;
			   result = a / b;
		   }
		   else if(operation[op] == '*'){
			   result = num1 * num2;
		   }
		   char buf[10];
		   int N1digit = intToStr(num1, buf, 0);  // number of digit for first number
		   int N2digit = intToStr(num2, buf, 0);  // number of digit for second number
		   int Redigit = LCD_sendfloat(result, buf, 2);// number of digit for anser
		   //Choose a random position and place a question mark in its place so that the person can guess what the number or operation is here.
		   int idx = rand() % (N1digit + N2digit + Redigit + 2);
		   LCD_sendFloat(num1, buf, 0);
		   if(idx < N1digit){
			   anser = buf[idx];
			   buf[idx] = '?';
			   flag3 = 1;
		   }
		   LCD_vSend_string(buf);
		   if(idx == N1digit && !flag3){
			    anser = operation[op];	
				LCD_vSend_char('?');
				flag3 = 1;
		   }
		   else {
			   LCD_vSend_char(operation[op]);
		   }
		   
		   LCD_sendFloat(num2, buf, 0);
		   N1digit++;
		   if(idx - N1digit < N2digit && !flag3){
			   anser = buf[idx - N1digit];
			   buf[idx - N1digit] = '?';
			   flag3 = 1;
		   }
		   LCD_vSend_string(buf);
		   
		   if(idx == N1digit + N2digit && !flag3){
			   anser = '=';
			   LCD_vSend_string("?");
			   flag3 = 1;
		   }
		   else {
			   LCD_vSend_char('=');
		   }
		   if(flagNegative == 1){
			   if(idx == (N1digit + N2digit + 1) && !flag3){
				   anser = '-';
				   LCD_vSend_char('?');
				   flag3 = 1;
			   }
			   else {
				  LCD_vSend_char('-'); 
			   }
			   N2digit++;
		   }
		   LCD_sendFloat(result, buf, 2);
		   
		   if(idx - (N1digit + N2digit + 1) < Redigit && !flag3){
			   anser = buf[idx - (N1digit + N2digit + 1)];
			   buf[idx - (N1digit + N2digit + 1)] = '?';
			   flag3 = 1;
			   LCD_movecursor(1, (N1digit + N2digit + 2));
		   }
		   LCD_vSend_string(buf);
	   }
	   	
	   
	    x=keypad_u8check_press();
		   
	   while(x==NOTPRESSED && flag2==0 ){
		   if(counter1 >= 1200 && flag4 == 0)
		   {
			   flag2=1;
		   }
		   x=keypad_u8check_press();
	   } 
	   
	   if(x == 'A'){
		   LCD_clearscreen();
		   flagNegative = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, x = NOTPRESSED;
		   counter1 = 0, level = 0;
		   goto label;
	   }
	   else if(flag2 == 1){
		   LCD_clearscreen();
		   LCD_movecursor(2, 4);
		   LCD_vSend_string("Time over");
		   _delay_ms(1500);
		   LCD_clearscreen();
		   LCD_movecursor(2, 4);
		   LCD_vSend_string("Game over");
		   flag4 = 1, flag2 = 0;
	   } 
	   else if(x == anser){
		   LCD_clearscreen();
		   LCD_movecursor(2, 4);
		   LCD_vSend_string("Great Work");
		   _delay_ms(1500);
		   LCD_clearscreen();
		   LCD_movecursor(1, 4);
		   LCD_vSend_string("Level ");
		   level++;
		   char buf[10];
		   LCD_sendFloat(level, buf, 0);
		   LCD_vSend_char(buf);
		   _delay_ms(1500);
		   LCD_clearscreen();
		   flagNegative = 0, flag1 = 0, flag2 = 0, flag3 = 0,flag4 = 0, x = NOTPRESSED;
		   counter1 = 0;
	   }
	   else if(x != anser ){
		   LCD_clearscreen();
		   LCD_movecursor(2, 4);
		   LCD_vSend_string("Wrong anser");
		   _delay_ms(1500);
		   LCD_clearscreen();
		   LCD_movecursor(1,2);
		   LCD_vSend_string("The correct");
		   LCD_movecursor(2, 2);
		   LCD_vSend_string("answer = ");
		   LCD_vSend_char(anser);
		   _delay_ms(1500);
		   LCD_clearscreen();
		   LCD_movecursor(2, 4);
		   LCD_vSend_string("Game over");	
		   flag4 = 1;		 
			   
	   }
	   
   }   
      
}

ISR(TIMER0_COMP_vect){
	counter1++;
}
