MediaStreamDevicesController::~MediaStreamDevicesController() {
  if (!callback_.is_null()) {
    callback_.Run(content::MediaStreamDevices(),
                  scoped_ptr<content::MediaStreamUI>());
  }
}
