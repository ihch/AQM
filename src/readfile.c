#include <stdio.h>
#include <stdlib.h>
#include "aqm.h"
#include "readfile.h"


/**
 *  function: readfile
 *  description: 波形ファイルのデータ読み込み
 *  args:
 *    結果を格納する配列
 *    EchoData *echoData
 *
 *  return:
 *    int:
 *      読み込みが成功したか:
 *        - EXIT_SUCCESS
 *        - EXIT_FAILURE
 * 
 **/
int readfile(EchoData *echoData) {
  FILE *fp;
  char readbuf[MAX_LINE_LENGTH] = {'\0'};

  if ((fp = fopen(INPUT_FILE, "r")) == NULL) {
    return EXIT_FAILURE;
  }

  int i = 0;
  while (i < ECHODATA_LENGTH && fgets(readbuf, MAX_LINE_LENGTH, fp) != NULL) {
    echoData->data[i++] = strtod(readbuf, NULL);
  }

  return EXIT_SUCCESS;
}

