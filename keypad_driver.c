/*
 * keypad_driver.c
 *
 * Created: 11/6/2023 12:52:11 PM
 *  Author: Dell
 */ 
 #include "keypad_driver.h"
 #include "DIO.h"
 #define portK 'D'
 void keypad_vInit()
 {
  DIO_set_port_direction(portK, 0x0f);
  DIO_vconnectpullup(portK,4,1);
  DIO_vconnectpullup(portK,5,1);
  DIO_vconnectpullup(portK,6,1);
  DIO_vconnectpullup(portK,7,1);
   
 }
 char keypad_u8check_press()
 {
  char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
// char arr[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'A','0','=','+'}};  
  char row,coloumn,x;
  char returnval=NOTPRESSED;
  for(row=0;row<4;row++)
  {
  DIO_write(portK,0,1);
  DIO_write(portK,1,1);
  DIO_write(portK,2,1);
  DIO_write(portK,3,1);
  DIO_write(portK,row,0);
 
  for(coloumn=0;coloumn<4;coloumn++)
  {
   x=DIO_u8read(portK,(coloumn+4));
   if(x==0)
    {
     returnval=arr[row][coloumn];
     break;
    }  
  } 
  if(x==0)
  {
   break;
  }
 }  
  return returnval ;  
 }
 