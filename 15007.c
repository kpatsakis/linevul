Camera3Device::PreparerThread::~PreparerThread() {
 Thread::requestExitAndWait();
 if (mCurrentStream != nullptr) {
        mCurrentStream->cancelPrepare();
        ATRACE_ASYNC_END("stream prepare", mCurrentStream->getId());
        mCurrentStream.clear();
 }
    clear();
}
