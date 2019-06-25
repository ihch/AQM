#include <stdio.h>
#include <stdlib.h>
#include "acf.h"
#include "readfile.h"


double acf(WaveData *waveData, int start, int d) {
  double sum = 0.0L;

  for (int i = start; i < ACF_RANGE - d; i++) {
    sum += waveData->data[i] * waveData->data[i + d];
  }

  return sum;
}

int example_acf(void) {
  WaveData waveData;

  if (readfile(&waveData) == EXIT_FAILURE) {
    return -1;
  }

  printf("%lf\n", acf(&waveData, 5));

  return 0;
}
