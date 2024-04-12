status_t OMXNodeInstance::getState(OMX_STATETYPE* state) {
 Mutex::Autolock autoLock(mLock);

    OMX_ERRORTYPE err = OMX_GetState(mHandle, state);
    CLOG_IF_ERROR(getState, err, "");
 return StatusFromOMXError(err);
}
