Camera2Client::~Camera2Client() {
    ATRACE_CALL();
    ALOGV("~Camera2Client");

    mDestructionStarted = true;

    disconnect();

    ALOGI("Camera %d: Closed", mCameraId);

 }
