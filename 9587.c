bool Histogram::InspectConstructionArguments(const std::string& name,
                                             Sample* minimum,
                                             Sample* maximum,
                                             uint32_t* bucket_count) {
  if (*minimum < 1) {
    DVLOG(1) << "Histogram: " << name << " has bad minimum: " << *minimum;
    *minimum = 1;
  }
  if (*maximum >= kSampleType_MAX) {
    DVLOG(1) << "Histogram: " << name << " has bad maximum: " << *maximum;
    *maximum = kSampleType_MAX - 1;
  }
  if (*bucket_count >= kBucketCount_MAX) {
    DVLOG(1) << "Histogram: " << name << " has bad bucket_count: "
             << *bucket_count;
    *bucket_count = kBucketCount_MAX - 1;
  }

  if (*minimum >= *maximum)
    return false;
  if (*bucket_count < 3)
    return false;
  if (*bucket_count > static_cast<uint32_t>(*maximum - *minimum + 2))
    return false;
  return true;
}
