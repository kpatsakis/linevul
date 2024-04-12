int GetQuicReducedPingTimeoutSeconds(
    const VariationParameters& quic_trial_params) {
  int value;
  if (base::StringToInt(
          GetVariationParam(quic_trial_params, "reduced_ping_timeout_seconds"),
          &value)) {
    return value;
  }
  return 0;
}
