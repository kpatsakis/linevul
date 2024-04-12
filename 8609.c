void ManualFillingControllerImpl::Hide(FillingSource source) {
  if (source == FillingSource::AUTOFILL &&
      !base::FeatureList::IsEnabled(
          autofill::features::kAutofillKeyboardAccessory)) {
    return;
  }
  visible_sources_.erase(source);
  if (visible_sources_.empty())
    view_->Hide();
}
