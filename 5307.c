  Factory(const std::string& name,
          HistogramType histogram_type,
          HistogramBase::Sample minimum,
          HistogramBase::Sample maximum,
          uint32_t bucket_count,
          int32_t flags)
    : name_(name),
      histogram_type_(histogram_type),
      minimum_(minimum),
      maximum_(maximum),
      bucket_count_(bucket_count),
      flags_(flags) {}
