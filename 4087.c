  virtual std::unique_ptr<HistogramBase> HeapAlloc(const BucketRanges* ranges) {
    return WrapUnique(new Histogram(name_, minimum_, maximum_, ranges));
  }
