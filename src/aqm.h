// include guard
#ifndef INCLUDED_AQM
#define INCLUDED_AQM
// code
#define INPUT_FILENAME "input.csv"
#define WAVEDATA_LENGTH 10000

typedef struct WaveData {
  double data[WAVEDATA_LENGTH + 10];
} WaveData;

#endif
