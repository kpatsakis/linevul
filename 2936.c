void InputDispatcher::dispatchOnce() {
 nsecs_t nextWakeupTime = LONG_LONG_MAX;
 { // acquire lock
 AutoMutex _l(mLock);
        mDispatcherIsAliveCondition.broadcast();

 if (!haveCommandsLocked()) {
            dispatchOnceInnerLocked(&nextWakeupTime);
 }

 if (runCommandsLockedInterruptible()) {
            nextWakeupTime = LONG_LONG_MIN;
 }
 } // release lock

 nsecs_t currentTime = now();
 int timeoutMillis = toMillisecondTimeoutDelay(currentTime, nextWakeupTime);
    mLooper->pollOnce(timeoutMillis);
}
