/*
 * DIO.h
 *
 * Created: 10/21/2023 7:55:30 AM
 *  Author: Dell
 */ 


#ifndef DIO_H_
#define DIO_H_

unsigned char DIO_read_port(unsigned char portname);
void DIO_write_port(unsigned char portname,unsigned char portvalue);
void DIO_toggle(unsigned char portname,unsigned char pinnumber);
unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber);
void DIO_Write(unsigned char portname, unsigned char pin, unsigned char outputvalue);
void DIO_vsetPINDir(unsigned char portname, unsigned char pin, unsigned char direction);
void DIO_set_port_direction(unsigned char portname, unsigned char direction);
void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup);
void write_low_nibble(unsigned char portname,unsigned char value);
void write_high_nibble(unsigned char portname,unsigned char value);



#endif /* DIO_H_ */