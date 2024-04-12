std::unique_ptr<HistogramSamples> Histogram::SnapshotFinalDelta() const {
  DCHECK(!final_delta_created_);
  final_delta_created_ = true;

  std::unique_ptr<HistogramSamples> snapshot = SnapshotSampleVector();

  if (logged_samples_)
    snapshot->Subtract(*logged_samples_);
  return snapshot;
}
