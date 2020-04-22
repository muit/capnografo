#ifndef SENSOR_H
#define SENSOR_H

extern long sensorData[1000];
extern unsigned int dataIndex;
extern unsigned int sensorSampleTime;
extern unsigned int sensorMaxSamples;

int parseSprintIR(void);
void setupSprintIR(void);


/**
 * @brief  This function looks for the maximum in the sensor data interval
 * @note   Will move to sensor
 * @param  startingIndex: Starting index of the search (included)
 * @param  endingIndex: Ending index of the search (included)
 * @retval 
 */
long getMaxDataSensorValue(unsigned int startingIndex, unsigned int endingIndex);


#endif