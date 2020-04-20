#ifndef SENSOR_H
#define SENSOR_H

extern long sensorData[1000];
extern unsigned int dataIndex;
extern unsigned int sensorSampleTime;
extern unsigned int sensorMaxSamples;

int parseSprintIR(void);
void setupSprintIR(void);

#endif