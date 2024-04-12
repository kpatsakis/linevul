void OutOfProcessInstance::DocumentHasUnsupportedFeature(
    const std::string& feature) {
  std::string metric("PDF_Unsupported_");
  metric += feature;
  if (!unsupported_features_reported_.count(metric)) {
    unsupported_features_reported_.insert(metric);
    UserMetricsRecordAction(metric);
  }

  if (!full_)
    return;

  if (told_browser_about_unsupported_feature_)
    return;
  told_browser_about_unsupported_feature_ = true;

  pp::PDF::HasUnsupportedFeature(this);
}
