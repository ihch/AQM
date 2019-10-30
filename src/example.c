#include <stdio.h>
#include <stdlib.h>

#include "aqm.h"
#include "acf.h"
#include "readfile.h"
#include "findpeaks.h"

int main(void) { 
  EchoData echoData;
  Acf nolag_acf[SEA_FLOOR_DEPTH / ACF_INTERVAL + 10];
  Acf max_acf[SEA_FLOOR_DEPTH / ACF_INTERVAL + 10];
  Peak peaks[ECHODATA_LENGTH / 2 + 10] = {0};
  Peak result[ECHODATA_LENGTH / 2 / MIN_PEAK_DISTANCE + 10] = {0};
  FILE *output_file = NULL;

  if (readfile(&echoData) == EXIT_FAILURE) {
    return -1;
  }
  acf_control(&echoData, ACF_RANGE, ACF_INTERVAL, SEA_FLOOR_DEPTH, nolag_acf, max_acf);

  output_file = fopen(OUTPUT_FILE, "w");
  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) fprintf(output_file, ",");
    fprintf(output_file, "%lf", nolag_acf[i].acf_result);
  }
  fprintf(output_file, "\n");
  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) fprintf(output_file, ",");
    fprintf(output_file, "%lf", max_acf[i].acf_result);
  }
  fprintf(output_file, "\n");
  for (int i = 0; i < SEA_FLOOR_DEPTH / ACF_INTERVAL - 1; i++) {
    if (i != 0) fprintf(output_file, ",");
    fprintf(output_file, "%d", max_acf[i].lag);
  }
  fprintf(output_file, "\n\n");

  fprintf(output_file, "### findpeaks ###\n");
  findpeaks(&echoData, UPPER_LIMIT, LOWER_LIMIT, MIN_PEAK_DISTANCE, peaks, result);
  for (int i = 0; i < sizeof(result) / sizeof(Peak); i++) {
    fprintf(output_file, "i: %d, depth: %d, peak: %d\n", i, result[i].depth, result[i].peak_value);
  }

  return 0;
}
