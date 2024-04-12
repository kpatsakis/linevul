std::unique_ptr<HistogramBase> BooleanHistogram::PersistentCreate(
    const std::string& name,
    const BucketRanges* ranges,
    HistogramBase::AtomicCount* counts,
    HistogramBase::AtomicCount* logged_counts,
    HistogramSamples::Metadata* meta,
    HistogramSamples::Metadata* logged_meta) {
  return WrapUnique(new BooleanHistogram(
      name, ranges, counts, logged_counts, meta, logged_meta));
}
