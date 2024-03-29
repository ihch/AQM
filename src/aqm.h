// include guard
#ifndef INCLUDED_AQM
#define INCLUDED_AQM
// code
#define ECHODATA_LENGTH 10000

typedef struct EchoData {
  double data[ECHODATA_LENGTH + 10];
} EchoData;

typedef struct Acf {
  double acf_result;
  int lag;
} Acf;

#endif
