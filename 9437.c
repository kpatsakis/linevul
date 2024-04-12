bool ShouldEnableQuic(base::StringPiece quic_trial_group,
                      const VariationParameters& quic_trial_params,
                      bool is_quic_force_disabled,
                      bool is_quic_force_enabled) {
  if (is_quic_force_disabled)
    return false;
  if (is_quic_force_enabled)
    return true;

  return quic_trial_group.starts_with(kQuicFieldTrialEnabledGroupName) ||
         quic_trial_group.starts_with(kQuicFieldTrialHttpsEnabledGroupName) ||
         base::LowerCaseEqualsASCII(
             GetVariationParam(quic_trial_params, "enable_quic"), "true");
}
