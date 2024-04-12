void Camera3Device::sNotify(const camera3_callback_ops *cb,
 const camera3_notify_msg *msg) {
 Camera3Device *d =
 const_cast<Camera3Device*>(static_cast<const Camera3Device*>(cb));
    d->notify(msg);
}
