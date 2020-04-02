
#pragma once


class SensorAdapter {};

class Sensor
{
public:
    float lastValue = 0.f;

    Sensor() {}
    virtual ~Sensor() {}

    virtual void Start() {}
    virtual void Record(RecordingSet& record) = 0;
};

class Sensor_SprintIRBase : public Sensor
{
protected:
    i32 frequency = 20;
    i32 serialBaudRate = 9600;

private:

    char printBuffer[33];
    HardwareSerial sensorSerial {2};


public:

    Sensor_SprintIR() : Sensor() {}

    virtual void Start() override
    {
        sensorSerial.begin(serialBaudRate);
    }

    virtual void Record(RecordingSet& record) override
    {
        // Wait for a new chain of values
        while(sensorSerial.read() != 'Z') {}

        u32 co2filteredRX = sensorSerial.parseInt();
        u32 co2rawRX = sensorSerial.parseInt();

        // Record value
        lastValue = float(co2rawRX) / 1000.f;
        record.RecordValue(lastValue);
    }
};


class Sensor_SprintIR_R : public Sensor_SprintIRBase
{
public:
    Sensor_SprintIR_R() : Sensor_SprintIRBase()
    {
        frequency = 50;
        serialBaudRate = 38400;
    }
};


class Sensor_MockAnalog : public Sensor
{
    static constexpr u32 pin = 34;
    static constexpr float minValue = 0.f;
    static constexpr float maxValue = 60.f;


public:

    virtual void Record(RecordingSet& record) override
    {
        // Read signal 4 times and average value
        u16 value = 0;
        for(u8 i = 0; i < 4; ++i)
        {
            value += analogRead(pin);
            delayMicroseconds(50);
        }
        value /= 4;
        
        // Record value
        const float value01 = float(value) / 4096;
        lastValue = minValue + (value01 * (maxValue - minValue));

        record.RecordValue(lastValue);
    }
};
