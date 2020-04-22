#ifndef ANALYSIS_H
#define ANALYSIS_H


// Finite State Machine state list:
#define WAIT_BASELINE (0)
#define BASELINE      (1)
#define EXP_UPSTROKE  (2)
#define EXP_PLATEAU   (3)
#define INSPIRATION   (4)



#define LOW_CO2_LIMIT  (1000) // PPM
#define BASELINE_COUNT_MIN (10) // Minimum consecutive measures under LOW_CO2_LIMIT to get to state BASELINE
#define BASELINE_COUNT_MAX (500) // Used for apnea alarm, 

#define UPSTROKE_COUNT_MIN (5) // Filter for getting to UPSTROKE state

#define PLATEAU_MAX_INC    (100) // Max inclination to consider a plateau
#define PLATEAU_COUNT_MIN  (5) 

#define INSPIRATION_MIN_INC  (100)
#define INSPIRATION_COUNT_MIN  (5)

#define BPM_PRINT_INTERVAL (3) // Number of breath to count before send the BPM

void analyzeData(void);

#endif