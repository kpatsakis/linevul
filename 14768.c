bool MediaStreamDevicesController::IsSchemeSecure() const {
  return (request_.security_origin.SchemeIsSecure());
}
