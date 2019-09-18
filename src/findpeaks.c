#include "acf.h"
#include "readfile.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Peak {
  int depth;
  int peak_value;
} Peak;

void all_peaks(EchoData *echoData, int upper_limit, int lower_limit, Peak *peaks);
void findpeaks(EchoData *echoData, int upper_limit, int lower_limit, int min_peak_distance, Peak *peaks);
void distance_filter(int min_peak_distance, Peak *peaks, Peak *result);

/* compare and sort */
int compare(const Peak *peak1, const Peak *peak2);

/*
int main(void) {
  EchoData echoData;
  int upper_limit = 40000, lower_limit = 3000;
  int min_peak_distance = 30;
  Peak peaks[3010] = {};

  if (readfile(&echoData) == EXIT_FAILURE) {
    return -1;
  }
  all_peaks(&echoData, upper_limit, lower_limit, peaks);
  // findpeaks(&echoData, upper_limit, lower_limit, min_peak_distance, peaks);
  qsort(
      peaks,
      sizeof(peaks) / sizeof(peaks[0]),
      sizeof(Peak),
      (int (*)(const void *, const void *))compare
  );

  for (int i = 0; i < 3000; i++) {
    printf("i: %d, depth: %d v: %d\n", i, peaks[i].depth, peaks[i].peak_value);
    // printf("i: %d, v: %lf\n", i, echoData.data[i]);
  }
}
*/

int compare(const Peak *peak1, const Peak *peak2) {
  if (peak1->peak_value > peak2->peak_value) { return -1; }
  if (peak1->peak_value < peak2->peak_value) { return 1; }
  if (peak1->depth < peak2->depth) { return -1; }
  return 1;
}

void all_peaks(EchoData *echoData, int upper_limit, int lower_limit, Peak *peaks) {
  int peak_pos = 0;
  for (int i = 1; i < ECHODATA_LENGTH - 1; i++) {
    double lv = echoData->data[i - 1];
    double v = echoData->data[i];
    double rv = echoData->data[i + 1];

    if (lv >= v || rv >= v) continue;
    if (v < lower_limit || upper_limit < v) continue;
    if (i <= 100) { printf("i: %d, lv: %.2lf, v: %.2lf, rv: %.2lf\n", i, lv, v, rv); }

    peaks[peak_pos++] = (Peak){i, v};
  }
}

void distance_filter(int min_peak_distance, Peak *peaks, Peak *result) {
  // peaksを降順に見てmin_peak_distanceの範囲にあるものは入れない
}

void findpeaks(EchoData *echoData, int upper_limit, int lower_limit, int min_peak_distance, Peak *peaks) {
  Peak result[3010];
  all_peaks(echoData, upper_limit, lower_limit, peaks);
  // filter by min_peak_distance
  distance_filter(min_peak_distance, peaks, result);
}

