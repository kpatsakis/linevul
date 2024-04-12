SparseHistogram::SparseHistogram(const std::string& name)
    : HistogramBase(name),
      samples_(new SampleMap(HashMetricName(name))),
      logged_samples_(new SampleMap(samples_->id())) {}
