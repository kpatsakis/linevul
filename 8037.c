static uint64_t btsnoop_timestamp(void) {
 struct timeval tv;
  gettimeofday(&tv, NULL);

 uint64_t timestamp = tv.tv_sec * 1000 * 1000LL;
  timestamp += tv.tv_usec;
  timestamp += BTSNOOP_EPOCH_DELTA;
 return timestamp;
}
