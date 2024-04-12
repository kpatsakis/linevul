status_t Camera3Device::RequestThread::queueTrigger(
 RequestTrigger trigger[],
 size_t count) {

 Mutex::Autolock l(mTriggerMutex);
 status_t ret;

 for (size_t i = 0; i < count; ++i) {
        ret = queueTriggerLocked(trigger[i]);

 if (ret != OK) {
 return ret;
 }
 }

 return OK;
}
