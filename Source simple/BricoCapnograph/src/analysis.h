#ifndef ANALYSIS_H
#define ANALYSIS_H

#define WAIT_BASELINE (0)
#define BASELINE      (1)
#define EXP_UPSTROKE  (2)
#define EXP_PLATEAU   (3)
#define INSPIRATION   (4)



#define LOW_CO2_LIMIT  (1000)
#define BASELINE_COUNT_MIN (10)
#define BASELINE_COUNT_MAX (500)

#define UPSTROKE_COUNT_MIN (5)

#define PLATEAU_MAX_INC    (100)
#define PLATEAU_COUNT_MIN  (5)

#define INSPIRATION_MIN_INC  (100)
#define INSPIRATION_COUNT_MIN  (5)


void analyzeData(void);

#endif