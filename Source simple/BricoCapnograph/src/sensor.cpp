#include <Arduino.h>
#include "sensor.h"
#include "display.h"

HardwareSerial sensor(2); //U2TX 17, U2RX16

#define SENSOR_DATA_LENGTH 1000

long sensorData[SENSOR_DATA_LENGTH];
unsigned int dataIndex = 0;

unsigned int sensorMult = 0;
unsigned int sensorSampleTime = 0;
unsigned int sensorMaxSamples = 0;


/**
 * @brief  Find the maximum in the range of the sensor data. Simple approach
 * @note   
 * @param  startIndex: 
 * @param  finishIndex: 
 * @retval max in range
 */
long findMax(unsigned int startIndex, unsigned int finishIndex);


int parseSprintIR(void)
{
  unsigned long parseStart = millis();
  while(sensor.read()!='z')
  {
    if((millis()-parseStart)>(sensorSampleTime+5))
    {
        Serial.println("ERROR: Data dont´t arrive!");
        sensorData[dataIndex] = 0;
        if((dataIndex++)==sensorMaxSamples) dataIndex = 0;
        return -1;
    }
  }
  long co2rawRX = sensor.parseInt() * sensorMult;
  if(co2rawRX>99999)
  {
    Serial.println("ERROR: Bad Data");
    sensorData[dataIndex] = 0;
    if((dataIndex++)==sensorMaxSamples) dataIndex = 0;
    return -1;
  }
  sensorData[dataIndex] = co2rawRX;
  if((dataIndex++)==sensorMaxSamples)
  {
    dataIndex = 0;
  } 
  return 0;
}

void setupSprintIR(void)
{
  Serial.print("Searching SprintIR CO2 sensor...");
  display.setTextSize(2);
  display.setTextColor(COLOR_YELLOW);
  display.print("\nSEARCHING SENSOR:");
  //sensor.begin(9600);   //Other SprintIR sensors
  sensor.begin(38400);   //SprintIR-R 
  sensor.setTimeout(60); //Set parseInt timeout to 60ms
  delay(4500);            //wait serial & sensor start

  //get data multiplicator
  sensor.println(".");
  unsigned long loopStart = millis();
  while(sensor.read()!='.') //wait for the answer
  {
    if((millis()-loopStart)>100)
    {
        Serial.println("ERROR!\n  Sensor not found, please check your connections and reset!");
        display.println("\nERROR!\nSENSOR NOT FOUND!");
        while(1);
    }
  }  
  sensorMult = sensor.parseInt();
  Serial.print("Found!\n  Multiplicator is: ");
  display.print("OK\nMULTIPLICATOR: ");
  Serial.println(sensorMult);
  display.println(sensorMult);
  sensor.read();                //empty \r from the buffer
  sensor.read();                //empty \n from the buffer

  //setup sensor output
  Serial.print("  Waiting for first  data...");
  display.print("WAITING DATA1:");
  sensor.println("M 2");        // set output fields to only CO2 raw(z)
  sensor.println("K 1");        // set mode to streaming
  delay(500);
  //Check sensor streaming data and measure sample time
  if( parseSprintIR() == -1)
  {
      Serial.println("ERROR!\nSensor don´t send data, please check your connections and reset!");
      display.println("\nERROR!\nSENSOR DON'T SEND DATA!");
      while(1);
  }
  else
  {
    loopStart = millis();
    Serial.print("  Waiting for second data...");
    display.print("OK\nWAITING DATA2:");
    if(parseSprintIR()!=-1)
    {
      sensorSampleTime = millis()-loopStart;
      Serial.print(sensorSampleTime);
      Serial.println("ms");
      if((sensorSampleTime>40) && (sensorSampleTime<70))
      {
        sensorSampleTime = 50;
      }
      if((sensorSampleTime>0) && (sensorSampleTime<40))
      {
        sensorSampleTime = 20;
      }
      Serial.print("SprintIR CO2 sensor working and sending data each: ");
      Serial.print(sensorSampleTime);
      Serial.println("ms");
      display.print("OK\nSprintIR SENSOR OK!\nSAMPLE TIME: ");
      display.print(sensorSampleTime);
      display.println("ms");
      sensor.setTimeout(sensorSampleTime+5); //actualize parseInt timeout
    }
    else
    {
      Serial.println("ERROR!\nSensor don´t stream data, please check your connections and reset!");
      Serial.println("\nERROR!\nSENSOR DON'T STREAM DATA!");
      while(1);
    }
  }
}

long getMaxDataSensorValue(unsigned int startingIndex, unsigned int endingIndex)
{
  // sensorData
  // SENSOR_DATA_LENGTH
  long retVal = 0;

  if(startingIndex < endingIndex)
  {
    long firstRangeMax = findMax(startingIndex, SENSOR_DATA_LENGTH);
    long secondRangeMax = findMax(0, endingIndex);

    if (firstRangeMax>=secondRangeMax)
    {
      retVal = firstRangeMax;
    }
    else
    {
      retVal = secondRangeMax;
    }/* code */
    

  } else if(endingIndex > startingIndex)
  {
    retVal = findMax(startingIndex, endingIndex);
  }
  else
  {
    retVal = sensorData[startingIndex];
  }


  return retVal;
}

long findMax(unsigned int startIndex, unsigned int finishIndex)
{
  long retVal = sensorData[startIndex];
  for(unsigned int i = startIndex; i < finishIndex; i++)
  {
    if (sensorData[i]>retVal)
      retVal = sensorData[i];
  }
  return retVal;
}