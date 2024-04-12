void Histogram::WriteAsciiBucketContext(const int64_t past,
                                        const Count current,
                                        const int64_t remaining,
                                        const uint32_t i,
                                        std::string* output) const {
  double scaled_sum = (past + current + remaining) / 100.0;
  WriteAsciiBucketValue(current, scaled_sum, output);
  if (0 < i) {
    double percentage = past / scaled_sum;
    StringAppendF(output, " {%3.1f%%}", percentage);
  }
}
