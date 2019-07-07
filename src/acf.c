#include <stdio.h>
#include <stdlib.h>
#include "acf.h"

int acf_max(Acf *acfResult, int begin, int end);

void acf(double *echoData, int range, Acf *result) {
  for (int lag = 0; lag <= range; lag++) {
    double sum = 0.0L;
    for (int i = 0; i + lag <= range; i++) {
      sum += echoData[i] * echoData[i + lag];
    }
    result[lag].acf_result = sum;
    result[lag].lag = lag;
  }
}

void acf_control(EchoData *echoData, int range, int interval, int end, Acf *nolag_acf, Acf *max_acf) {
  Acf result[ACF_RANGE + 5];

  for (int i = 0; i * interval + range <= end; i++) {
    int max_lag;

    acf(&(echoData->data[i * interval]), range, result);
    nolag_acf[i].acf_result = result[0].acf_result;
    nolag_acf[i].lag = 0;

    max_lag = acf_max(result, 5, ACF_RANGE / 2);
    max_acf[i].acf_result = result[max_lag].acf_result;
    max_acf[i].lag = max_lag;
  }
}

int acf_max(Acf *acfResult, int begin, int end) {
  double max_ = 0.0L;
  int lag = -1;
  for (int i = begin; i < end; i++) {
    if (max_ <= (acfResult)[i].acf_result) {
      max_ = (acfResult)[i].acf_result;
      lag = (acfResult)[i].lag;
    }
  }

  return lag;
}

int main(void) { 
  EchoData echoData;
  Acf nolag_acf[SEA_FLOOR_DEPTH / ACF_INTERVAL + 10];
  Acf max_acf[SEA_FLOOR_DEPTH / ACF_INTERVAL + 10];

  if (readfile(&echoData) == EXIT_FAILURE) {
    return -1;
  }
  acf_control(&echoData, ACF_RANGE, ACF_INTERVAL, SEA_FLOOR_DEPTH, nolag_acf, max_acf);

  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) printf(",");
    printf("%lf", nolag_acf[i].acf_result);
  }
  printf("\n");
  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) printf(",");
    printf("%lf", max_acf[i].acf_result);
  }
  printf("\n");
  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) printf(",");
    printf("%d", max_acf[i].lag);
  }

  return 0;
}
