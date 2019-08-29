#include <stdio.h>
#include <stdlib.h>

#include "aqm.h"
#include "readfile.h"
#include "acf.h"

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
