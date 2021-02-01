// The function allows to read only the content of the device's Data Registers:
// Cap Data Register: H byte (AP=0x01), M byte (AP=0x02), L byte (AP=0x03).
// VT Data Register: H byte (AP=0x04), M byte (AP=0x05), L byte (AP=0x06).
// All three bytes of the data register are read sequentially 
// by using the address pointer auto-increment feature.

// 2021-01-29 by Mattia Devangelio <mattdev6@gmail.com>

void dataRegisters()
{
  int r=CAP_DATA_REG; //starting address: Cap Data H byte
  int Nbyte=6; //3 bytes Cap Data + 3 bytes VT Data
  int N=r+Nbyte; //Address Pointer index 

  unsigned char d[Nbyte],x;
  unsigned long readvalue[2];
  float data[2];
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

  //The contents of the three H-M-L registers are combined to create the 24-bit conversion result:
  readvalue[0]=((unsigned long)d[0]<<16)+((unsigned long)d[1]<<8)+(unsigned long)d[2];
  readvalue[1]=((unsigned long)d[3]<<16)+((unsigned long)d[4]<<8)+(unsigned long)d[5];
  
  data[0]=(((float)readvalue[0]-powf(2,23))/powf(2,23))*(float)caprange; //Capacitance reading
  data[1]=(((float)readvalue[1]-powf(2,23))/powf(2,23))*(float)vtrange; //Voltage reading

  Serial.print(data[0],5);
  Serial.print(" pF");
  Serial.print('\t');
  Serial.print(data[1],5);
  Serial.println(" V");
}
