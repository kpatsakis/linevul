CameraDeviceClientBase::CameraDeviceClientBase(
 const sp<CameraService>& cameraService,
 const sp<ICameraDeviceCallbacks>& remoteCallback,
 const String16& clientPackageName,
 int cameraId,
 int cameraFacing,
 int clientPid,
 uid_t clientUid,
 int servicePid) :
 BasicClient(cameraService, remoteCallback->asBinder(), clientPackageName,
                cameraId, cameraFacing, clientPid, clientUid, servicePid),
    mRemoteCallback(remoteCallback) {
}
