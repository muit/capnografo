/*
This a functional version of the analysis class for the capnometer. In a future
we may create a class, initialise it in the setup and then execute a runner
in loop.
*/
#include <cstdarg>
#include <Arduino.h>

#include <analysis.h>
#include "sensor.h"
#include "display.h"

unsigned int breathState = 0; // WAIT_BASELINE
unsigned int nextState = 0;   // WAIT_BASELINE
unsigned int lastState = 0;   // WAIT_BASELINE

unsigned int lastDataIndex = 0;

unsigned int baseline_CO2_count = 0;
unsigned int baseline_state_count = 0;
unsigned int upstroke_CO2_count = 0;
unsigned int plateau_CO2_count = 0;
unsigned int inspiration_CO2_count = 0;

unsigned int apneaAlarm = 0;


unsigned short int rpm_instantaneous = 0;
unsigned int bmp_lastSampleTime = 0;

// private functions

void logMessage(const char * , ...); // belongs to display actually

void breathStateIdentification(void);

void processAlarmApnea(void); 

void BreathPerMinuteCounter(void);

/**
 * @brief  process the data analysis in the hyperloop. It will identify the 
 * respiratory status, process alarms, stablish breath per minute, etc.
 * @note   This is the entry point for this interface
 * @retval None
 */
void analyzeData(void)
{
  if (dataIndex - 1 == 0)
    lastDataIndex = sensorMaxSamples - 1;
  else
    lastDataIndex = dataIndex - 2;

  breathStateIdentification();

  processAlarmApnea();

  //processAlarmNoReturnToBaseline()

  //

  BreathPerMinuteCounter();
}

/**
 * @brief  Identifies the breathing status and follows its evolution.
 * @note   It will evolve the state machine captured in breathState
 * @retval None
 */
void breathStateIdentification()
{
  lastState = breathState;
  breathState = nextState;

  switch (breathState)
  {
  case WAIT_BASELINE:
    if (lastState != breathState)
      logMessage("WAIT_BASELINE");

    //analize
    if (sensorData[dataIndex - 1] < LOW_CO2_LIMIT)
      baseline_CO2_count++;
    else
      baseline_CO2_count = 0;

    //transition
    if (baseline_CO2_count > BASELINE_COUNT_MIN)
    {
      baseline_CO2_count = 0;
      nextState = BASELINE;
    }
    break;

  case BASELINE:
    if (lastState != breathState)
    {
      logMessage("BASELINE");
    }
    //analize
    if (sensorData[dataIndex - 1] > sensorData[lastDataIndex])
      upstroke_CO2_count++;
    else
      upstroke_CO2_count = 0;

    baseline_state_count++; // Keep track of the cycles in the baseline_status

    //transition
    if (upstroke_CO2_count > UPSTROKE_COUNT_MIN)
    {
      baseline_state_count = 0;
      apneaAlarm = 0;
      nextState = EXP_UPSTROKE;
    }

    break;

  case EXP_UPSTROKE:
    if (lastState != breathState)
    {
      logMessage("EXP_UPSTROKE");
    }
    //analize
    if (sensorData[dataIndex - 1] - sensorData[lastDataIndex] < PLATEAU_MAX_INC)
      plateau_CO2_count++;
    else
      plateau_CO2_count = 0;
    //Alarms
    //check high CO2
    //transition
    if (plateau_CO2_count > PLATEAU_COUNT_MIN)
    {
      plateau_CO2_count = 0;
      nextState = EXP_PLATEAU;
    }
    //check inspiration/apnea
    /* What if we don't have a response flat enough but a suddent fall on CO_2 
    due to a very discontinuous cycle?
    */
    break;

  case EXP_PLATEAU:
    if (lastState != breathState)
    {
      logMessage("EXP_PLATEAU");
    }
    //analize
    if (sensorData[lastDataIndex] - sensorData[dataIndex - 1] > INSPIRATION_MIN_INC)
      inspiration_CO2_count++;
    else
      inspiration_CO2_count = 0;
    //Alarms
    //check high CO2
    //transition
    if (inspiration_CO2_count > INSPIRATION_COUNT_MIN)
    {
      inspiration_CO2_count = 0;
      nextState = INSPIRATION;
    }
    break;

  case INSPIRATION:
    if (lastState != breathState)
    {
      logMessage("INSPIRATION");
    }
    //analize
    if (sensorData[dataIndex - 1] < INSPIRATION_MIN_INC)
      baseline_CO2_count++;
    else
      baseline_CO2_count = 0;
    //Alarms
    //transition
    if (baseline_CO2_count > BASELINE_COUNT_MIN)
    {
      baseline_CO2_count = 0;
      nextState = BASELINE;
    }
    break;
  default:
    // let's catch this
    Serial.println("UNDEFINED BREATH STATE: next state is EXP_UPSTROKE");
    // ToDo: Analyse what data needs to be clean to start again
    nextState = EXP_UPSTROKE;
    break;
  }
}

/**
 * @brief  Identifies an Apnea event
 * @note   It is just a sketch, we need to connect it to listeners.
 * @retval None
 */
void processAlarmApnea()
{
  switch (breathState)
  {
  case BASELINE/* constant-expression */:
    if (baseline_state_count > BASELINE_COUNT_MAX)
    {
      if (apneaAlarm == 0)
      {
        apneaAlarm = 1; // Take actions
        logMessage("ALRM: APNEA");
      }

    }
    break;
  
  default:
    apneaAlarm = 0;
    break;
  }

}

/**
 * @brief  Identify the point where a new breath beggings and stimate the 
 * respirations per minute (rpm)
 * @note   It is just a sketch, we need to connect it to listeners.
 * @retval None
 */
void BreathPerMinuteCounter(void)
{
    if ((lastState != breathState) & (breathState == BASELINE))
    {
      int elapsedTime = sensorSampleTime - bmp_lastSampleTime;

      if(elapsedTime > 0)
      {
        rpm_instantaneous = 60*1000 / elapsedTime ;
       
        logMessage("BPM %i",rpm_instantaneous);
      }

      
      bmp_lastSampleTime = sensorSampleTime;
      
    }
}


/**
 * @brief  Auxiliar function to log the messages to the serial and display
 * @note   This is not the right location. If we want to print a badge in the
 * screen or do loggings it is better to include that as a facility of the 
 * display class
 * @param  format: 
 * @retval None
 * 
 * 
 * http://www.cplusplus.com/reference/cstdarg/
 * http://www.cplusplus.com/reference/cstdio/sprintf/
 */
void logMessage(const char * format, ...)
{
  std::va_list args;

  va_start(args,format);

  char formatedMsg[80];
  sprintf(formatedMsg, format, args);

  va_end(args);
  
  Serial.println(formatedMsg);
  /* ToDo: Defeer this to a function pointer
          representating things is not the analysis responsibility
        */
  display.fillRect(0, 30, 239, 60, COLOR_BLACK);
  display.setCursor(0, 30);
  display.print(formatedMsg);
  va_end(args);
}
