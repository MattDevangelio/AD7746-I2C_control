/* 
 * Filename: registers.h
 * Author: Mattia Devangelio <mattdev6@gmail.com>
 * Description: Header file.
 * License: Copyright (c) 2021, The library is licensed under the MIT license.
*/

#ifndef REGISTERS_H
#define REGISTERS_H

#include <Wire.h>
#include <math.h>

#define ADDRESS_CDC 0x48 
#define RESET_ADDRESS 0xBF
#define N_REG 19

// AD7746 Registers List
#define STATUS_REG 0x00
#define CAP_DATA_REG 0x01
#define VT_DATA_REG 0x04
#define CAP_SETUP_REG 0x07
#define VT_SETUP_REG 0x08
#define EXC_SETUP_REG 0x09
#define CONFIGURATION_REG 0x0A
#define CAP_DAC_A_REG 0x0B
#define CAP_DAC_B_REG 0x0C
#define CAP_OFFSET_REG 0x0D
#define CAP_GAIN_REG 0x0F
#define VOLT_GAIN_REG 0x11

#define caprange 4.096 //Picofarads
#define vtrange 3.3 //Volts
// The voltage range is set according to the voltage reference: REFIN(+)=3.3 V, REFIN(-)=0 V 
// set 1.17 V if the internal reference is used (ref input pins left as an open circuit or connected to GND)

void setRegister(int r, int val);
float readRegister(int r);

#endif
