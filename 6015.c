bool Document::AllowedToUseDynamicMarkUpInsertion(
    const char* api_name,
    ExceptionState& exception_state) {
  if (!RuntimeEnabledFeatures::ExperimentalProductivityFeaturesEnabled()) {
    return true;
  }
  if (!frame_ || IsFeatureEnabled(mojom::FeaturePolicyFeature::kDocumentWrite,
                                  ReportOptions::kReportOnFailure)) {
    return true;
  }

  exception_state.ThrowDOMException(
      DOMExceptionCode::kNotAllowedError,
      String::Format(
          "The use of method '%s' has been blocked by feature policy. The "
          "feature "
          "'document-write' is disabled in this document.",
          api_name));
  return false;
}
