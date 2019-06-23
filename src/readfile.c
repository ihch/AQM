#include <stdio.h>
#include <stdlib.h>
#include "aqm.h"


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

  if ((fp = fopen(INPUT_FILENAME, "r")) == NULL) {
    // error処理
    return EXIT_FAILURE;
  }
}
