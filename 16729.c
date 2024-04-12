bool HTMLMediaElement::hasSelectedVideoTrack() {
  DCHECK(RuntimeEnabledFeatures::backgroundVideoTrackOptimizationEnabled());

  return m_videoTracks && m_videoTracks->selectedIndex() != -1;
}
