#ifndef INCLUDED_ACF
#define INCLUDED_ACF

#include "aqm.h"

#define ACF_RANGE 200
#define ACF_INTERVAL 100
#define ACF_END 4000

double acf(WaveData *waveData, int start, int d);

#endif // INCLUDED_ACF
