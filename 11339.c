  void SetMetrics(OomInterventionMetrics metrics) {
    metrics_ = std::make_unique<OomInterventionMetrics>();
    *metrics_ = metrics;
  }
