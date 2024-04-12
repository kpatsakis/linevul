void ImageCapture::UpdateMediaTrackCapabilities(
    media::mojom::blink::PhotoStatePtr photo_state) {
  if (!photo_state)
    return;

  WTF::Vector<WTF::String> supported_white_balance_modes;
  supported_white_balance_modes.ReserveInitialCapacity(
      photo_state->supported_white_balance_modes.size());
  for (const auto& supported_mode : photo_state->supported_white_balance_modes)
    supported_white_balance_modes.push_back(ToString(supported_mode));
  if (!supported_white_balance_modes.IsEmpty()) {
    capabilities_.setWhiteBalanceMode(std::move(supported_white_balance_modes));
    settings_.setWhiteBalanceMode(
        ToString(photo_state->current_white_balance_mode));
  }

  WTF::Vector<WTF::String> supported_exposure_modes;
  supported_exposure_modes.ReserveInitialCapacity(
      photo_state->supported_exposure_modes.size());
  for (const auto& supported_mode : photo_state->supported_exposure_modes)
    supported_exposure_modes.push_back(ToString(supported_mode));
  if (!supported_exposure_modes.IsEmpty()) {
    capabilities_.setExposureMode(std::move(supported_exposure_modes));
    settings_.setExposureMode(ToString(photo_state->current_exposure_mode));
  }

  WTF::Vector<WTF::String> supported_focus_modes;
  supported_focus_modes.ReserveInitialCapacity(
      photo_state->supported_focus_modes.size());
  for (const auto& supported_mode : photo_state->supported_focus_modes)
    supported_focus_modes.push_back(ToString(supported_mode));
  if (!supported_focus_modes.IsEmpty()) {
    capabilities_.setFocusMode(std::move(supported_focus_modes));
    settings_.setFocusMode(ToString(photo_state->current_focus_mode));
  }

  HeapVector<Point2D> current_points_of_interest;
  if (!photo_state->points_of_interest.IsEmpty()) {
    for (const auto& point : photo_state->points_of_interest) {
      Point2D web_point;
      web_point.setX(point->x);
      web_point.setY(point->y);
      current_points_of_interest.push_back(mojo::Clone(web_point));
    }
  }
  settings_.setPointsOfInterest(std::move(current_points_of_interest));

  if (photo_state->exposure_compensation->max !=
      photo_state->exposure_compensation->min) {
    capabilities_.setExposureCompensation(
        MediaSettingsRange::Create(*photo_state->exposure_compensation));
    settings_.setExposureCompensation(
        photo_state->exposure_compensation->current);
  }
  if (photo_state->color_temperature->max !=
      photo_state->color_temperature->min) {
    capabilities_.setColorTemperature(
        MediaSettingsRange::Create(*photo_state->color_temperature));
    settings_.setColorTemperature(photo_state->color_temperature->current);
  }
  if (photo_state->iso->max != photo_state->iso->min) {
    capabilities_.setIso(MediaSettingsRange::Create(*photo_state->iso));
    settings_.setIso(photo_state->iso->current);
  }

  if (photo_state->brightness->max != photo_state->brightness->min) {
    capabilities_.setBrightness(
        MediaSettingsRange::Create(*photo_state->brightness));
    settings_.setBrightness(photo_state->brightness->current);
  }
  if (photo_state->contrast->max != photo_state->contrast->min) {
    capabilities_.setContrast(
        MediaSettingsRange::Create(*photo_state->contrast));
    settings_.setContrast(photo_state->contrast->current);
  }
  if (photo_state->saturation->max != photo_state->saturation->min) {
    capabilities_.setSaturation(
        MediaSettingsRange::Create(*photo_state->saturation));
    settings_.setSaturation(photo_state->saturation->current);
  }
  if (photo_state->sharpness->max != photo_state->sharpness->min) {
    capabilities_.setSharpness(
        MediaSettingsRange::Create(*photo_state->sharpness));
    settings_.setSharpness(photo_state->sharpness->current);
  }

  if (photo_state->zoom->max != photo_state->zoom->min) {
    capabilities_.setZoom(MediaSettingsRange::Create(*photo_state->zoom));
    settings_.setZoom(photo_state->zoom->current);
  }

  if (photo_state->supports_torch)
    capabilities_.setTorch(photo_state->supports_torch);
  if (photo_state->supports_torch)
    settings_.setTorch(photo_state->torch);
}
