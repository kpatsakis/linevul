void CameraSource::DeathNotifier::binderDied(const wp<IBinder>& who __unused) {
    ALOGI("Camera recording proxy died");
}
