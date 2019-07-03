// include guard
#ifndef INCLUDED_AQM
#define INCLUDED_AQM
// code
#define INPUT_FILENAME "input.csv"
#define ECHODATA_LENGTH 10000

typedef struct EchoData {
  double data[ECHODATA_LENGTH + 10];
} EchoData;

#endif
