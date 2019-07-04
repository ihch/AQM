#ifndef INCLUDED_ACF
#define INCLUDED_ACF

#include "aqm.h"
#include "readfile.h"

#define ACF_RANGE 200
#define ACF_INTERVAL 100
#define ACF_END 4000

double acf(EchoData *echoData, int begin, int end, int d);

#endif // INCLUDED_ACF
