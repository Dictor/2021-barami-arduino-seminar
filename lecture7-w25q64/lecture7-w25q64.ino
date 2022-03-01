#include <SPI.h>

#define W25Q64_INST_WRITE_ENABLE 0x06
#define W25Q64_INST_READ_UNIQUE_ID 0x4B
#define W25Q64_INST_READ_DATA 0x03
#define W25Q64_INST_PAGE_PROGRAM 0x02

SPISettings spiConfig(2000000, LSBFIRST, SPI_MODE3);
uint8_t txBuffer[16], rxBuffer[8], inputBuffer[8];

void setup()
{
  SPI.begin(4);
  SPI.beginTransaction(spiConfig);
  Serial.begin(115200);

  serialWrite("start program\n");

  readRegister(W25Q64_INST_READ_UNIQUE_ID, txBuffer, 4, rxBuffer, 8);
  serialWrite("unique ID : ");
  serialWrite8(rxBuffer);
  serialWrite("\n");

  writeCommand(W25Q64_INST_WRITE_ENABLE);
  serialWrite("enable write\n");
}

void loop()
{
  readData();
  serialWrite("data : ");
  serialWrite8(rxBuffer);
  serialWrite("\n");

  serialWrite("enter new data : ");
  while (1)
  {
    if (Serial.available() >= 8)
    {
      for (int i = 0; i < 8; i++)
      {
        inputBuffer[i] = Serial.read();
      }
      writePage(inputBuffer);
      serialWrite("writing done!\n");
      break;
    }
  }
}

void writeCommand(uint8_t data)
{
  SPI.transfer(data);
}

void writeRegister(uint8_t addr, uint8_t *data, uint8_t length)
{
  SPI.transfer(addr, SPI_CONTINUE);
  for (int i = 0; i < length - 1; i++)
  {
    SPI.transfer(data[i], SPI_CONTINUE);
  }
  SPI.transfer(data[length - 1]);
}

void readRegister(uint8_t addr, uint8_t *writeData, uint8_t writeLength, uint8_t *readData, uint8_t readLength)
{
  SPI.transfer(addr, SPI_CONTINUE);
  for (int i = 0; i < writeLength; i++)
  {
    SPI.transfer(writeData[i], SPI_CONTINUE);
  }
  for (int i = 0; i < readLength - 1; i++)
  {
    readData[i] = SPI.transfer(0x00, SPI_CONTINUE);
  }
  readData[readLength - 1] = SPI.transfer(0x00);
}

void readData()
{
  txBuffer[0] = 0;
  txBuffer[1] = 0;
  txBuffer[2] = 0;
  readRegister(W25Q64_INST_READ_DATA, txBuffer, 3, rxBuffer, 8);
}

void writePage(uint8_t *data)
{
  txBuffer[0] = 0;
  txBuffer[1] = 0;
  txBuffer[2] = 0;
  for (int i = 0; i < 8; i++) {
    txBuffer[3 + i] = data[i];
  }
  
  writeRegister(W25Q64_INST_PAGE_PROGRAM, txBuffer, 11);
}

void serialWrite(const char *s, ...)
{
  va_list args;
  va_start(args, s);
  int n = vsnprintf(NULL, 0, s, args);
  char *str = new char[n + 1];
  vsprintf(str, s, args);
  va_end(args);
  Serial.print(str);
  delete[] str;
}

void serialWrite8(uint8_t *array)
{
  serialWrite("%c %c %c %c %c %c %c %c", array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7]);
}
