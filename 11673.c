void AudioOutputAuthorizationHandler::OverridePermissionsForTesting(
    bool override_value) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  permission_checker_.reset(new MediaDevicesPermissionChecker(override_value));
}
