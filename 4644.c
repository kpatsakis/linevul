static bool ApproximatelyEqual(const SkMatrix& a, const SkMatrix& b) {
  static constexpr float kTolerance = 1e-5f;
  for (int i = 0; i < 9; i++) {
    if (std::abs(a[i] - b[i]) > kTolerance)
      return false;
  }
  return true;
}
