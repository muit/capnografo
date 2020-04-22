#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>

#include "display.h"
#include "sensor.h"
#include "main.h"

unsigned int samplesPerPixel = 0;
unsigned int samplesReceived = 0;
unsigned int graphOffset = 0;

Adafruit_ST7789 display = 
    Adafruit_ST7789(DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN);

void setupDisplay(void)
{
  display.init(DISPLAY_X_SIZE, DISPLAY_Y_SIZE, SPI_MODE2);// Init ST7789 display
  display.fillScreen(COLOR_BLACK);
  display.enableTearing(false);
  display.setRotation(1);
  display.setCursor(0, 0);
  display.setTextColor(COLOR_MAGENTA);
  display.setTextSize(4);
  display.println("CAPNOGRAPH");
  display.setTextSize(3);
  display.println("     V0.1");
}

void printDisplay(void)
{
  if(samplesReceived==0)
  {
    //Serial.println(sensorData[dataIndex-1]);
    display.setCursor(0, 0);
    display.fillRect(0,0,239,30,COLOR_BLACK);
    display.setTextSize(4);
    display.setCursor(0, 0);
    display.print(sensorData[dataIndex-1]);
    
    int plotIndex = 0;
    for(int currentLine = (DISPLAY_X_SIZE-1); 
      (currentLine + 1) >= (DISPLAY_X_SIZE-((dataIndex-1)/samplesPerPixel));
      currentLine--)
    {
      long dataToPlot = sensorData[dataIndex-1-plotIndex];
      display.drawLine( currentLine,
                  (DISPLAY_Y_SIZE/2), 
                  currentLine,
                  (DISPLAY_Y_SIZE-1),
                  COLOR_BLACK);
      display.drawLine(currentLine, 
                      map(dataToPlot,
                        0,
                        60000,
                        (DISPLAY_Y_SIZE-1),
                        (DISPLAY_Y_SIZE/2)),
                      currentLine,
                      (DISPLAY_Y_SIZE-1),
                      COLOR_YELLOW);
      plotIndex += samplesPerPixel ;
      /*
      Serial.print(" D D");
      Serial.print(dataIndex-1);
      Serial.print(" L");
      Serial.print(currentLine);
      Serial.print(" P");
      Serial.println(dataIndex-1-(plotIndex-samplesPerPixel));*/
    }
    int invplotIndex = sensorMaxSamples - samplesPerPixel;
    for(int currentInvLine = (DISPLAY_X_SIZE-1)-((dataIndex+samplesPerPixel)/samplesPerPixel); 
      currentInvLine >= 0;
      currentInvLine--)
    {
      long dataInvToPlot = sensorData[invplotIndex];
      display.drawLine( currentInvLine,
                  (DISPLAY_Y_SIZE/2), 
                  currentInvLine,
                  (DISPLAY_Y_SIZE-1),
                  COLOR_BLACK);
      display.drawLine(currentInvLine, 
                      map(dataInvToPlot,
                        0,
                        60000,
                        (DISPLAY_Y_SIZE-1),
                        (DISPLAY_Y_SIZE/2)),
                      currentInvLine,
                      (DISPLAY_Y_SIZE-1),
                      COLOR_YELLOW);
      invplotIndex -= samplesPerPixel;
      /*
      Serial.print("I D");
      Serial.print(dataIndex-1);
      Serial.print(" L");
      Serial.print(currentInvLine);
      Serial.print(" P");
      Serial.println(invplotIndex+samplesPerPixel);*/
    }
    samplesReceived++;
    if(samplesReceived==samplesPerPixel) samplesReceived=0;
  }
  else
  {
    samplesReceived++;
    if(samplesReceived==samplesPerPixel) samplesReceived=0;
  }
}

void setupGraph(void)
{
  int totalMsDisplay = 0;
  samplesPerPixel = 0;
  while (totalMsDisplay<10000)
  {
      totalMsDisplay = sensorSampleTime * ++samplesPerPixel * DISPLAY_Y_SIZE;
  }
  sensorMaxSamples = (DISPLAY_Y_SIZE * samplesPerPixel);

  Serial.print("samplesPerPixel:");
  Serial.println(samplesPerPixel);
  Serial.print("sensorMaxSamples:");
  Serial.println(sensorMaxSamples);
  Serial.print("totalMsDisplay:");
  Serial.println(totalMsDisplay);
  delay(1000);
}

/**
 * @brief  Print in the assigned portion of the screen the Breaths per minute
 * @note   
 * @param  bpm: breaths per minutes
 * @retval None
 */
void printBPM(unsigned int bpm)
{
  // Compose the string. No longer that 10 characters
  char formatedMsg[10];
  sprintf(formatedMsg, "BPM %i", bpm); //BPM XXX(7)
  
  //Clean the needed area
  display.fillRect(0, 60, 239, 90, COLOR_BLACK);
  
  // Set the pen in place
  display.setCursor(0, 60);

  // Write the message
  display.print(formatedMsg);

}

/**
 * @brief  Print in the assigned portion of the screen the Breaths per minute
 * @note   
 * @param  etCO2: The value of etCO2 in percentage (%) 
 * @retval None
 */
void printEtCO2(unsigned int etCO2)
{
  // Compose the string. No longer that 10 characters
  char formatedMsg[10];
  sprintf(formatedMsg, "etCO2 %i/%", etCO2); //etCO2 XXX%(9)
  
  //Clean the needed area
  display.fillRect(0, 90, 239, 120, COLOR_BLACK);
  
  // Set the pen in place
  display.setCursor(0, 90);

  // Write the message
  display.print(formatedMsg);

}