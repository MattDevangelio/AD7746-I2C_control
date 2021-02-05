/* 
 *  Filename: registers.cpp
 *  Author: Mattia Devangelio <mattdev6@gmail.com>
 *  Description: Implemented functions for Read/Write operations on the AD7746 Registers.
 *  License: Copyright (c) 2021, The library is licensed under the MIT license.
 */

#include "registers.h"

// Write an integer value to any addressed register whose AP is: 
// 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x11.

void setRegister(int r, int val)
{
  Wire.beginTransmission(ADDRESS_CDC);
  Wire.write(r);
  if(r==CAP_OFFSET_REG || r==CAP_GAIN_REG || r==VOLT_GAIN_REG)
  {
    if(val>=0 && val<pow(2,8))
    {
      Wire.write(0);
      Wire.endTransmission();
      
      Wire.beginTransmission(ADDRESS_CDC);
      Wire.write(r+1);
      Wire.write(val);
    }
    else if(val>=pow(2,8) && val<pow(2,16))
    {
      Wire.write(val>>8);
      Wire.endTransmission();
      
      Wire.beginTransmission(ADDRESS_CDC);
      Wire.write(r+1);
      Wire.write(val&=(int)(pow(2,8)-1));
    }
  }
  else
  {
    if(val>=0)
    Wire.write(val);
  }
  Wire.endTransmission();
}

// Read the stored value in any addressed register. 
// For reading values encoded in more than 1 byte, 
// it is sufficient to address only the first register related to the H byte:
// 3-byte values: 0x01 Cap Data, 0x04 VT Data, 
// 2-byte values: 0x0D Cap Offset, 0x0F Cap Gain, 0x11 Volt Gain

float readRegister(int r)
{
  int N=0;
  int Nbyte;
  if(r==CAP_DATA_REG || r==VT_DATA_REG)
  {
    Nbyte=3;
  }
  else if(r==CAP_OFFSET_REG || r==CAP_GAIN_REG || r==VOLT_GAIN_REG)
  {
    Nbyte=2;
  }
  else
  {
    Nbyte=1;
  }
  N=r+Nbyte;

  unsigned char d[Nbyte],x;
  unsigned long readvalue;
  char i=0;
  
  setRegister(STATUS_REG,-1);
  Wire.requestFrom(ADDRESS_CDC,N);
  while(i<N)
  {
  while(!Wire.available()==N){
    }
  x=Wire.read();
  if(i>r-1)
    d[i-r]=x;
  i++;
  }

  if(Nbyte==3)
  {
    readvalue=((unsigned long)d[0]<<16)+((unsigned long)d[1]<<8)+(unsigned long)d[2];
    float fullrange;
    if(r==CAP_DATA_REG)
    {
      fullrange=(float)caprange;
    }
    else if(r==VT_DATA_REG)
    {
      fullrange=(float)vtrange;
    }
    float data=(((float)readvalue-powf(2,23))/powf(2,23))*fullrange;
    return data;
  }
  else
  {
    if(Nbyte==2)
    {
      readvalue=((unsigned long)d[0]<<8)+(unsigned long)d[1];
     }
    else if(Nbyte==1)
    {
      readvalue=(unsigned long)d[0];
     }
    return (float)readvalue;
   }
}
