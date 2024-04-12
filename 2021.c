void BrowserView::SetIntentPickerViewVisibility(bool visible) {
  LocationBarView* location_bar = GetLocationBarView();

  if (!location_bar->intent_picker_view())
    return;

  if (location_bar->intent_picker_view()->visible() != visible) {
    location_bar->intent_picker_view()->SetVisible(visible);
    location_bar->Layout();
  }
}
