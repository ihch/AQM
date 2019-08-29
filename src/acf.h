#ifndef INCLUDED_ACF
#define INCLUDED_ACF

#include "aqm.h"
#include "readfile.h"

#define ACF_RANGE 200
#define ACF_INTERVAL 100
#define SEA_FLOOR_DEPTH 1170

void acf(double *echoData, int range, Acf *result);
void acf_control(EchoData *echoData, int range, int interval, int end, Acf *nolag_acf, Acf *max_acf);
int acf_max(Acf *acfResult, int begin, int end);

#endif // INCLUDED_ACF
