bool ShouldQuicHeadersIncludeH2StreamDependencies(
    const VariationParameters& quic_trial_params) {
  return base::LowerCaseEqualsASCII(
      GetVariationParam(quic_trial_params,
                        "headers_include_h2_stream_dependency"),
      "true");
}
