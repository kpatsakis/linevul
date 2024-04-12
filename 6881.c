error::Error GLES2DecoderImpl::HandleRequestExtensionCHROMIUM(
    uint32 immediate_data_size, const gles2::RequestExtensionCHROMIUM& c) {
  Bucket* bucket = GetBucket(c.bucket_id);
  if (!bucket || bucket->size() == 0) {
    return error::kInvalidArguments;
  }
  std::string feature_str;
  if (!bucket->GetAsString(&feature_str)) {
    return error::kInvalidArguments;
  }

  bool std_derivatives_enabled =
      feature_info_->feature_flags().oes_standard_derivatives;
  bool webglsl_enabled =
      feature_info_->feature_flags().chromium_webglsl;

  feature_info_->AddFeatures(feature_str.c_str());

  bool initialization_required = false;
  if (force_webgl_glsl_validation_ && !derivatives_explicitly_enabled_) {
    size_t derivatives_offset = feature_str.find(kOESDerivativeExtension);
    if (std::string::npos != derivatives_offset) {
      derivatives_explicitly_enabled_ = true;
      initialization_required = true;
    }
  }

  if (std_derivatives_enabled !=
          feature_info_->feature_flags().oes_standard_derivatives ||
      webglsl_enabled !=
          feature_info_->feature_flags().chromium_webglsl ||
      initialization_required) {
    InitializeShaderTranslator();
  }

  UpdateCapabilities();

  return error::kNoError;
}
