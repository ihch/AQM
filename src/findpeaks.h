#ifndef INCLUDED_FINDPEAKS
#define INCLUDED_FINDPEAKS

#define UPPER_LIMIT (40000)
#define LOWER_LIMIT (3000)
#define MIN_PEAK_DISTANCE (30)

typedef struct Peak {
  int depth;
  int peak_value;
} Peak;

void all_peaks(EchoData *echoData, int upper_limit, int lower_limit, Peak *peaks);
void findpeaks(EchoData *echoData, int upper_limit, int lower_limit, int min_peak_distance, Peak *peaks, Peak *result);
void distance_filter(int min_peak_distance, Peak *peaks, Peak result[]);
int compare_peakvalue(const void *p1, const void *p2);
int compare_depth(const void *p1, const void *p2);

#endif // INCLUDED_FINDPEAKS
