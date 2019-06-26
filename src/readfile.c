#include <stdio.h>
#include <stdlib.h>
#include "readfile.h"


/***
 *  args:
 *    WaveData *waveData
 *
 *  return:
 *    int:
 *      読み込みが成功したか:
 *        - EXIT_SUCCESS
 *        - EXIT_FAILURE
 * 
 ***/
int readfile(WaveData *waveData) {
  FILE *fp;
  char readbuf[MAX_LINE_LENGTH] = {'\0'};

  if ((fp = fopen(INPUT_FILENAME, "r")) == NULL) {
    return EXIT_FAILURE;
  }

  int i = 0;
  while (i < WAVEDATA_LENGTH && fgets(readbuf, MAX_LINE_LENGTH, fp) != NULL) {
    waveData->data[i++] = strtod(readbuf, NULL);
  }

  return EXIT_SUCCESS;
}

int test_read(void) {
  WaveData waveData;
  readfile(&waveData);

  // for (int i = 0; i < WAVEDATA_LENGTH; i++) {
  for (int i = 0; i < 100; i++) {
    printf("%lf\n", waveData.data[i]);
  }

  return 0;
}
