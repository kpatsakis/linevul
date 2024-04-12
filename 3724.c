void Camera3Device::RequestThread::setErrorState(const char *fmt, ...) {
    sp<Camera3Device> parent = mParent.promote();
 if (parent != NULL) {
        va_list args;
        va_start(args, fmt);

        parent->setErrorStateV(fmt, args);

        va_end(args);
 }
}
