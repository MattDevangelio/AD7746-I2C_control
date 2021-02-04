/* 
 * Filename: allregisters.ino
 * Author: Mattia Devangelio <mattdev6@gmail.com>
 * Description: Read and display on Serial Monitor the status of the AD7746 registers.
 * License: Copyright (c) 2021, The library is licensed under the MIT license.
*/

// The allRegisters function is implemented in order to display the real-time values of all the AD7746 registers.
// This reads by I2C communication protocol (Wire.h Library) 19 device's registers, according to AD7746 Datasheet,
// Copyright (c) Analog Devices, storing the relative content into a data array, and then printing it.
 

void allRegisters()
{
  setRegister(STATUS_REG,-1);
  Wire.requestFrom(ADDRESS_CDC,N_REG);

  unsigned char d[N_REG];
  char i=0;
  while (i<N_REG)
  {
  while(!Wire.available()==N_REG){
    }
  d[i] = Wire.read();
  i++;
  }

  unsigned long capvalue=((unsigned long)d[CAP_DATA_REG]<<16)+((unsigned long)d[CAP_DATA_REG+1]<<8)+(unsigned long)d[CAP_DATA_REG+2];
  float capdata=(((float)capvalue-powf(2,23))/powf(2,23))*(float)caprange;
  
  unsigned long vtvalue=((unsigned long)d[VT_DATA_REG]<<16)+((unsigned long)d[VT_DATA_REG+1]<<8)+(unsigned long)d[VT_DATA_REG+2];
  float vtdata=(((float)vtvalue-powf(2,23))/powf(2,23))*(float)vtrange; 
  
  unsigned long offset=((unsigned long)d[CAP_OFFSET_REG]<<8)+(unsigned long)d[CAP_OFFSET_REG+1];
  unsigned long capgain=((unsigned long)d[CAP_GAIN_REG]<<8)+(unsigned long)d[CAP_GAIN_REG+1];
  unsigned long vtgain=((unsigned long)d[VOLT_GAIN_REG]<<8)+(unsigned long)d[VOLT_GAIN_REG+1];

  Serial.print("status: ");
  Serial.print(d[STATUS_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[STATUS_REG]);
  Serial.print("cap data: ");
  Serial.print(d[CAP_DATA_REG],BIN);
  Serial.print(".");
  Serial.print(d[CAP_DATA_REG+1],BIN);
  Serial.print(".");
  Serial.print(d[CAP_DATA_REG+2],BIN);
  Serial.print(" / ");
  Serial.print(capvalue);
  Serial.print(" / ");
  Serial.print(capdata,5);
  Serial.println(" pF");
  Serial.print("vt data: ");
  Serial.print(d[VT_DATA_REG],BIN);
  Serial.print(".");
  Serial.print(d[VT_DATA_REG+1],BIN);
  Serial.print(".");
  Serial.print(d[VT_DATA_REG+2],BIN);
  Serial.print(" / ");
  Serial.print(vtvalue);
  Serial.print(" / ");
  Serial.print(vtdata,5);
  Serial.println(" V");
  Serial.print("cap setup: ");
  Serial.print(d[CAP_SETUP_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[CAP_SETUP_REG]);
  Serial.print("vt setup: ");
  Serial.print(d[VT_SETUP_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[VT_SETUP_REG]);
  Serial.print("exc setup: ");
  Serial.print(d[EXC_SETUP_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[EXC_SETUP_REG]);
  Serial.print("configuration: ");
  Serial.print(d[CONFIGURATION_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[CONFIGURATION_REG]);
  Serial.print("cap dac A: ");
  Serial.print(d[CAP_DAC_A_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[CAP_DAC_A_REG]);
  Serial.print("cap dac B: ");
  Serial.print(d[CAP_DAC_B_REG],BIN);
  Serial.print(" / ");
  Serial.println(d[CAP_DAC_B_REG]);
  Serial.print("cap offset: ");
  Serial.print(d[CAP_OFFSET_REG],BIN);
  Serial.print(".");
  Serial.print(d[CAP_OFFSET_REG+1],BIN);
  Serial.print(" / ");
  Serial.println(offset);
  Serial.print("cap gain: ");
  Serial.print(d[CAP_GAIN_REG],BIN);
  Serial.print(".");
  Serial.print(d[CAP_GAIN_REG+1],BIN);
  Serial.print(" / ");
  Serial.println(capgain);
  Serial.print("volt gain: ");
  Serial.print(d[VOLT_GAIN_REG],BIN);
  Serial.print(".");
  Serial.print(d[VOLT_GAIN_REG+1],BIN);
  Serial.print(" / ");
  Serial.println(vtgain);
  Serial.println("");
}
