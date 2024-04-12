static void addRange(vector<uint32_t> &coverage, uint32_t start, uint32_t end) {
#ifdef PRINTF_DEBUG
    printf("adding range %d-%d\n", start, end);
#endif
 if (coverage.empty() || coverage.back() < start) {
        coverage.push_back(start);
        coverage.push_back(end);
 } else {
        coverage.back() = end;

     }
 }
