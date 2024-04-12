bool HTMLMediaElement::ShouldShowControls(
    const RecordMetricsBehavior record_metrics) const {
  Settings* settings = GetDocument().GetSettings();
  if (settings && !settings->GetMediaControlsEnabled()) {
    if (record_metrics == RecordMetricsBehavior::kDoRecord)
      ShowControlsHistogram().Count(kMediaControlsShowDisabledSettings);
    return false;
  }

  if (FastHasAttribute(controlsAttr)) {
    if (record_metrics == RecordMetricsBehavior::kDoRecord)
      ShowControlsHistogram().Count(kMediaControlsShowAttribute);
    return true;
  }

  if (IsFullscreen()) {
    if (record_metrics == RecordMetricsBehavior::kDoRecord)
      ShowControlsHistogram().Count(kMediaControlsShowFullscreen);
    return true;
  }

  LocalFrame* frame = GetDocument().GetFrame();
  if (frame && !GetDocument().CanExecuteScripts(kNotAboutToExecuteScript)) {
    if (record_metrics == RecordMetricsBehavior::kDoRecord)
      ShowControlsHistogram().Count(kMediaControlsShowNoScript);
    return true;
  }

  if (record_metrics == RecordMetricsBehavior::kDoRecord)
    ShowControlsHistogram().Count(kMediaControlsShowNotShown);
  return false;
}
