void HTMLMediaElement::updateControlsVisibility() {
  if (!isConnected()) {
    if (mediaControls())
      mediaControls()->hide();
    return;
  }

  ensureMediaControls();
  mediaControls()->reset();

  if (shouldShowControls(RecordMetricsBehavior::DoRecord))
    mediaControls()->show();
  else
    mediaControls()->hide();
}
