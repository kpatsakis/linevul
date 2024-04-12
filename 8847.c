bool HTMLMediaElement::mediaTracksEnabledInternally() {
  return RuntimeEnabledFeatures::audioVideoTracksEnabled() ||
         RuntimeEnabledFeatures::backgroundVideoTrackOptimizationEnabled();
}
