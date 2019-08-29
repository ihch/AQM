#include <stdio.h>
#include <stdlib.h>
#include "readfile.h"


/***
 *  args:
 *    EchoData *echoData
 *
 *  return:
 *    int:
 *      読み込みが成功したか:
 *        - EXIT_SUCCESS
 *        - EXIT_FAILURE
 * 
 ***/
int readfile(EchoData *echoData) {
  FILE *fp;
  char readbuf[MAX_LINE_LENGTH] = {'\0'};

  if ((fp = fopen(INPUT_FILENAME, "r")) == NULL) {
    return EXIT_FAILURE;
  }

  int i = 0;
  while (i < ECHODATA_LENGTH && fgets(readbuf, MAX_LINE_LENGTH, fp) != NULL) {
    echoData->data[i++] = strtod(readbuf, NULL);
  }

  return EXIT_SUCCESS;
}

int test_read(void) {
  EchoData echoData;
  readfile(&echoData);

  // for (int i = 0; i < ECHODATA_LENGTH; i++) {
  for (int i = 0; i < 100; i++) {
    printf("%lf\n", echoData.data[i]);
  }

  return 0;
}
