void ACodec::ExecutingState::stateEntered() {
    ALOGV("[%s] Now Executing", mCodec->mComponentName.c_str());

    mCodec->mRenderTracker.clear(systemTime(CLOCK_MONOTONIC));
    mCodec->processDeferredMessages();
}
