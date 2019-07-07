#include <stdio.h>
#include <stdlib.h>
#include "acf.h"

int acf_max(Acf *acfResult, int begin, int end);

/***
 *  args:
 *    double *echoData  : acfの開始位置のポインタ
 *    int range         : acfの範囲
 *    Acf *result       : acfの結果
 ***/
void acf(double *echoData, int range, Acf *result) {
  /* 0 <= lag <= range の範囲のacfを求める */
  for (int lag = 0; lag <= range; lag++) {
    double sum = 0.0L;
    for (int i = 0; i + lag <= range; i++) {
      sum += echoData[i] * echoData[i + lag];
    }
    result[lag].acf_result = sum;
    result[lag].lag = lag;
  }
}

/***
 *  args:
 *    EchoData *echoData  : 波形データ
 *    int range           : acfの範囲
 *    int interval        : acfをずらしていく間隔
 *    int end             : acfにかける終端の位置
 *    Acf *nolag_acf      : lagなしのacfの値を保存する配列
 *    Acf *max_acf        : ある範囲でのacfの最大値を保存する配列
 ***/
void acf_control(EchoData *echoData, int range, int interval, int end, Acf *nolag_acf, Acf *max_acf) {
  Acf result[ACF_RANGE + 5];

  for (int i = 0; i * interval + range <= end; i++) {
    int max_lag;

    /* dataのi * interval番目からrangeの範囲でacfを計算 */
    acf(&(echoData->data[i * interval]), range, result);

    /* lag = 0のacfの結果を保存 */
    nolag_acf[i].acf_result = result[0].acf_result;
    nolag_acf[i].lag = 0;

    /* 求めた範囲でacfの値が最大になったlagを探す */
    max_lag = acf_max(result, 5, ACF_RANGE / 2);
    /* 求めた範囲でのacfの最大値とそのlagを保存 */
    max_acf[i].acf_result = result[max_lag].acf_result;
    max_acf[i].lag = max_lag;
  }
}

/***
 *  args:
 *    Acf *acfResult  : acfの結果の配列
 *    int begin       : 最大値を求める範囲の開始位置
 *    int end         : 最大値を求める範囲の終端位置
 *
 *  return:
 *    int:
 *      最大値が保存されているlagの値
 *        - begin <= lag <= end
 ***/
int acf_max(Acf *acfResult, int begin, int end) {
  double max_ = 0.0L;
  int lag = -1;

  for (int i = begin; i <= end; i++) {
    if (max_ <= (acfResult)[i].acf_result) {
      max_ = (acfResult)[i].acf_result;
      lag = (acfResult)[i].lag;
    }
  }

  return lag;
}

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
