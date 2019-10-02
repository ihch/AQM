#include <string.h>
#include "acf.h"
#include "readfile.h"
#include "findpeaks.h"

/**
 *  function: compare
 *  description: Peak構造体の比較関数
 *  ars:
 *    const Peak *peak1
 *    const Peak *peak2
 *
 *  return:
 *    int: 左辺値と右辺値の比較
 *      - 左辺が右辺より大きい 1
*       - 等しい 0
*       - 左辺が右辺より小さい -1
 **/
int compare(const Peak *peak1, const Peak *peak2) {
  if (peak1->peak_value > peak2->peak_value) { return -1; }
  if (peak1->peak_value < peak2->peak_value) { return 1; }
  if (peak1->depth < peak2->depth) { return -1; }
  return 1;
}

/**
 *  function: all_peaks
 *  description: 波形中の全ピーク抽出
 *  args:
 *    EchoData *echoData
 *    int upper_limit ピークの最大値
 *    int lower_limit ピークの最小値
 *
 *    結果を格納する配列
 *    Peak *peaks 全ピーク
 *
 *  return:
 *    void
 **/
void all_peaks(EchoData *echoData, int upper_limit, int lower_limit, Peak *peaks) {
  int peak_pos = 0;
  for (int i = 1; i < ECHODATA_LENGTH - 1; i++) {
    double lv = echoData->data[i - 1];
    double v = echoData->data[i];
    double rv = echoData->data[i + 1];

    /* 同じ値が連続する場合
       TODO ピークの位置の位置をどこにするか */
    if (lv == v) {
      for (int j = 0; j >= 0 && echoData->data[j] != v; j--) {
        lv = echoData->data[j];
      }
    }

    if (lv >= v || rv >= v) continue;
    if (v < lower_limit || upper_limit < v) continue;

    peaks[peak_pos++] = (Peak){i, v};
  }
}

/**
 *  function: distance_filter
 *  description: 全ピークに最小離隔距離でフィルターをする
 *  args:
 *    int min_peak_distance 最小離隔距離
 *    Peak *peaks 全ピーク
 *
 *    結果を格納する配列
 *    Peak *result min_peak_distance適用後のピーク
 *
 *  return:
 *    void
 **/
void distance_filter(int min_peak_distance, Peak *peaks, Peak *result) {
  // peaksを降順に見てmin_peak_distanceの範囲にあるものは入れない
  for (int i = 0; peaks[i].peak_value != 0; i++) {
    int index = peaks[i].depth / min_peak_distance;
    if (result[index].peak_value != 0) {
      continue;
    }
    result[index] = peaks[i];
  }
}

/**
 *  function: findpeaks
 *  description: 波形中のピーク抽出
 *  args:
 *    EchoData *echoData
 *    int upper_limit ピークの最大値
 *    int lower_limit ピークの最小値
 *    int min_peak_distance 最小離隔距離
 *
 *    結果を格納する配列
 *    Peak *peaks 全ピーク
 *    Peak *result min_peak_distance適用後のピーク
 *
 *  return:
 *    void
 **/
void findpeaks(EchoData *echoData, int upper_limit, int lower_limit, int min_peak_distance, Peak *peaks, Peak *result) {
  memset(result, 0, sizeof(Peak));
  all_peaks(echoData, upper_limit, lower_limit, peaks);
  distance_filter(min_peak_distance, peaks, result);
}
