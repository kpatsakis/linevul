static void* CreateHistogram(
    const char *name, int min, int max, size_t buckets) {
  Histogram* histogram = new Histogram(name, min, max, buckets);
  if (histogram) {
    histogram->SetFlags(kUmaTargetedHistogramFlag);
  }
  return histogram;
}
