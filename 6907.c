WebKitTestController* WebKitTestController::Get() {
  DCHECK(instance_);
  return instance_;
}
