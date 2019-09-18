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
int max_peak_pos(Peak *peaks, int len);

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

void findpeaks(EchoData *echoData, int upper_limit, int lower_limit, int min_peak_distance, Peak *peaks) {

  /*
  int peaks_pos = 0;
  for (int i = 1; i < ECHODATA_LENGTH; i++) {
    int lv = echoData->data[i - 1];
    int v = echoData->data[i];
    int rv = echoData->data[i + 1];
    int d = 1;
    for (int d = 1; lv == echoData->data[i] && i - d >= 0; d++) {
      lv = echoData->data[i - d];
    }
    for (int d = 1; rv == echoData->data[i] && i + d <= ECHODATA_LENGTH; d++) {
      rv = echoData->data[i + d];
    }
    printf("%d\n", i);
    printf("peaks_pos%d\n", peaks_pos);
    fflush(stdout);

    // if (lv < v && rv < v) {
    //   peaks[peaks_pos++] = (Peak){i, echoData->data[i]};
    // }
    if (v <= lv || v <= rv) { continue; }
    if (v < lower_limit || upper_limit < v) { continue; }
    // peaks[peaks_pos++] = (Peak){i, v};
    // 更新しながらmin_peak_distanceすると欲しい結果が消されることがある
    if (peaks_pos == 0) {
      peaks[peaks_pos++] = (Peak){i, v};
    }
    else {
      if (i - peaks[peaks_pos - 1].depth < min_peak_distance) {
        printf("before: %d, after: %d\n", peaks[peaks_pos - 1].depth, i);
        if (peaks[peaks_pos - 1].peak_value < v) {
          peaks[peaks_pos - 1] = (Peak){i, v};
        }
      }
      else {
        peaks[peaks_pos++] = (Peak){i, v};
      }
    }
  }
  */

  // min_peak_distanceする
  // for (int i = 0; i < peaks_pos; i++) {
  //   int max_pos = max_peak_pos(peaks, peaks_pos);
  //   printf("max_pos: %d, v: %d\n", max_pos, peaks[max_pos].peak_value);
  //   for (int j = max_pos - 1; j >= 0; j--) {
  //     if (peaks[max_pos].depth - peaks[j].depth < min_peak_distance) {
  //       peaks[j] = (Peak){0, 0};
  //     }
  //   }
  //   for (int j = max_pos + 1; j <= peaks_pos; j++) {
  //     if (peaks[j].depth - peaks[max_pos].depth < min_peak_distance) {
  //       peaks[j] = (Peak){0, 0};
  //     }
  //   }
  // }
}

int max_peak_pos(Peak *peak, int len) {
  int pos = 0;
  int max_ = 0;
  for (int i = 0; i <= len; i++) {
    if (max_ <= peak[i].peak_value) {
      max_ = peak[i].peak_value;
      pos = i;
    }
  }

  return pos;
}
