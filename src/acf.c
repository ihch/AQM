#include <stdio.h>
#include <stdlib.h>
#include "acf.h"
#include "readfile.h"


double acf(EchoData *echoData, int begin, int end, int d) {
  double sum = 0.0L;

  for (int i = begin; i <= end - d; i++) {
    sum += echoData->data[i] * echoData->data[i + d];
  }

  return sum;
}

int example_acf(void) {
  EchoData echoData;

  if (readfile(&echoData) == EXIT_FAILURE) {
    return -1;
  }

  for (int i = 0; i < 10; i++) {
    printf("%lf\n", acf(&echoData, ACF_INTERVAL * i, ACF_INTERVAL * i + ACF_RANGE, 0));
  }

  return 0;
}
