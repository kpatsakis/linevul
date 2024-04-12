bool MediaStreamDevicesController::ShouldAlwaysAllowOrigin() const {
  return profile_->GetHostContentSettingsMap()->ShouldAllowAllContent(
      request_.security_origin, request_.security_origin,
      CONTENT_SETTINGS_TYPE_MEDIASTREAM);
}
