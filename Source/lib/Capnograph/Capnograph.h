
#pragma once

#include "Alarm.h"
#include "UI.h"
#include "Sensor.h"
#include "Pattern.h"
#include "AllPatterns.h"
#include "Display/FrameTime.h"


class Capnograph
{
    // Change sensor type for different measuring devices.
    // E.g: Sensor_MockAnalog
    using SensorType = Sensor_SprintIRBase;


public:

    Alarm alarm;
    UI ui;
    SensorType sensor {};

    Pattern_Hiperventilation pattern_hiperventilation;
    Pattern_Hipoventilation pattern_hipoventilation;
    // List of patterns. First is higher priority.
    AnalysisPattern* analysisPatterns[2] {&pattern_hiperventilation, &pattern_hipoventilation};

    // 300 samples, 20hz = 15 seconds
    TInlineRecordingSet<300, 20> record {};
    FrameTime frame;


public:

    void Setup()
    {
        // No FPS cap as this is done by the sensor
        //frame.SetFPSCap(20);
        SetupPatterns();
        sensor.Start();
        ui.Start();
    }

    void Loop() {
        frame.Tick();

        sensor.Record(record);
        ui.Draw(*this);
        frame.PostTick();
    }

    static constexpr int GetNumPatterns() { return sizeof(analysisPatterns) / sizeof(AnalysisPattern*); }

protected:

    void SetupPatterns()
    {
        for(auto* pattern : analysisPatterns)
        {
            pattern->Setup(this);
        }
    }
};
