void HTMLMediaElement::automaticTrackSelectionForUpdatedUserPreference() {
  if (!m_textTracks || !m_textTracks->length())
    return;

  markCaptionAndSubtitleTracksAsUnconfigured();
  m_processingPreferenceChange = true;
  m_textTracksVisible = false;
  honorUserPreferencesForAutomaticTextTrackSelection();
  m_processingPreferenceChange = false;

  m_textTracksVisible = m_textTracks->hasShowingTracks();
  updateTextTrackDisplay();
}
