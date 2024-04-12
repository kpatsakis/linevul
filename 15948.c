void DataReductionProxySettings::SetCallbackToRegisterSyntheticFieldTrial(
    const SyntheticFieldTrialRegistrationCallback&
        on_data_reduction_proxy_enabled) {
  register_synthetic_field_trial_ = on_data_reduction_proxy_enabled;
   RegisterDataReductionProxyFieldTrial();
 }
