#include "acf.h"

/**
 *  function: acf
 *  description: ある範囲のacfを求める
 *  args:
 *    double *echoData  : acfの開始位置のポインタ
 *    int range         : acfの範囲
 *
 *    結果を格納する配列
 *    Acf *result       : acfの結果
 *
 *  return:
 *    void
 **/
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

/**
 *  function: acf_control
 *  description: acfの制御関数
 *  args:
 *    EchoData *echoData 波形データ
 *    int range acfの範囲
 *    int interval acfをずらしていく間隔
 *    int end  acfにかける終端の位置
 *
 *    結果を格納する配列
 *    Acf *nolag_acf lagなしのacfの値を保存する配列
 *    Acf *max_acf ある範囲でのacfの最大値を保存する配列
 *
 *  return:
 *    void
 **/
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

/**
 *  function: acf_max
 *  description: acfが最大になるlagの位置を求める
 *  args:
 *    Acf *acfResult acfの結果の配列
 *    int begin 最大値を求める範囲の開始位置
 *    int end 最大値を求める範囲の終端位置
 *
 *  return:
 *    int:
 *      最大値が保存されているlagの値
 *        - begin <= lag <= end
 **/
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
