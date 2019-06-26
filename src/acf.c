#include <stdio.h>
#include <stdlib.h>
#include "acf.h"
#include "readfile.h"


double acf(WaveData *waveData, int begin, int end, int d) {
  double sum = 0.0L;

  for (int i = begin; i <= end - d; i++) {
    sum += waveData->data[i] * waveData->data[i + d];
  }

  return sum;
}

int example_acf(void) {
  WaveData waveData;

  if (readfile(&waveData) == EXIT_FAILURE) {
    return -1;
  }

  for (int i = 0; i < 10; i++) {
    printf("%lf\n", acf(&waveData, ACF_INTERVAL * i, ACF_INTERVAL * i + ACF_RANGE, 0));
  }

  return 0;
}
