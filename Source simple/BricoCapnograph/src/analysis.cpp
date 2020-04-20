#include <Arduino.h>

#include <analysis.h>
#include "sensor.h"
#include "display.h"

unsigned int breathState = 0;
unsigned int nextState = 0;
unsigned int lastState = 0;

unsigned int lastDataIndex=0;

unsigned int baseline_CO2_count = 0;
unsigned int baseline_state_count = 0;
unsigned int upstroke_CO2_count = 0;
unsigned int plateau_CO2_count = 0;
unsigned int inspiration_CO2_count = 0;


unsigned int apneaAlarm = 0;

void analyzeData(void)
{
  if(dataIndex-1==0) lastDataIndex = sensorMaxSamples-1;
  else lastDataIndex = dataIndex-2;
  
  lastState = breathState;
  breathState = nextState;
  switch (breathState)
  {
    case WAIT_BASELINE:
      if(lastState != breathState) Serial.println("WAIT_BASELINE");
      //analize
      if (sensorData[dataIndex-1]<LOW_CO2_LIMIT)
        baseline_CO2_count++;
      else 
        baseline_CO2_count = 0;

      //transition
      if (baseline_CO2_count>BASELINE_COUNT_MIN)
      {
        baseline_CO2_count = 0;
        nextState = BASELINE;
      }
      break;

    case BASELINE:
      if(lastState != breathState)
      {
        Serial.println("BASELINE");
        display.fillRect(0,30,239,60,COLOR_BLACK);
        display.setCursor(0, 30);
        display.print("BASELINE");
      }
      //analize
      if (sensorData[dataIndex-1]>sensorData[lastDataIndex]) 
        upstroke_CO2_count++;
      else
        upstroke_CO2_count = 0;
      //alarm
      baseline_state_count++;
      if (baseline_state_count > BASELINE_COUNT_MAX) apneaAlarm = 1;
      //transition
      if (upstroke_CO2_count>UPSTROKE_COUNT_MIN)
      {
        baseline_state_count = 0;
        apneaAlarm = 0;
        nextState = EXP_UPSTROKE;
      }
      break;

    case EXP_UPSTROKE:
      if(lastState != breathState)
      {
        Serial.println("EXP_UPSTROKE");
        display.fillRect(0,30,239,60,COLOR_BLACK);
        display.setCursor(0, 30);
        display.print("EXP_UPSTRK");
      }
      //analize
      if (sensorData[dataIndex-1]-sensorData[lastDataIndex]<PLATEAU_MAX_INC) 
        plateau_CO2_count++;
      else
        plateau_CO2_count = 0;
      //Alarms
      //check high CO2
      //transition
      if (plateau_CO2_count>PLATEAU_COUNT_MIN)
      {
        plateau_CO2_count = 0;
        nextState = EXP_PLATEAU;
      }
      //check inspiration/apnea
      break;

    case EXP_PLATEAU:
      if(lastState != breathState)
      {
        Serial.println("EXP_PLATEAU");
        display.fillRect(0,30,239,60,COLOR_BLACK);
        display.setCursor(0, 30);
        display.print("EXP_PLAT");
      }
      //analize
      if (sensorData[lastDataIndex]-sensorData[dataIndex-1]>INSPIRATION_MIN_INC) 
        inspiration_CO2_count++;
      else
        inspiration_CO2_count = 0;
      //Alarms
      //check high CO2
      //transition
      if (inspiration_CO2_count>INSPIRATION_COUNT_MIN)
      {
        inspiration_CO2_count = 0;
        nextState = INSPIRATION;
      }
      break;

    case INSPIRATION:
      if(lastState != breathState)
      {
        Serial.println("INSPIRATION");
        display.fillRect(0,30,239,60,COLOR_BLACK);
        display.setCursor(0, 30);
        display.print("INSPIRAT");
      }
      //analize
      if (sensorData[dataIndex-1]<INSPIRATION_MIN_INC) 
        baseline_CO2_count++;
      else
        baseline_CO2_count = 0;
      //Alarms
      //transition
      if (baseline_CO2_count>BASELINE_COUNT_MIN)
      {
        baseline_CO2_count = 0;
        nextState = BASELINE;
      }
      break;
    default:
      break;
  }
}