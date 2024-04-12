bool ContentSecurityPolicy::ExperimentalFeaturesEnabled() const {
  return RuntimeEnabledFeatures::
      ExperimentalContentSecurityPolicyFeaturesEnabled();
}
