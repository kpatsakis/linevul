bool CCThreadProxy::compositeAndReadback(void *pixels, const IntRect& rect)
{
    TRACE_EVENT("CCThreadPRoxy::compositeAndReadback", this, 0);
    ASSERT(isMainThread());
    ASSERT(m_layerTreeHost);

    if (m_commitRequested)  {
        OwnPtr<CCMainThread::Task> beginFrameAndCommitTask;
        {
            CCMainThread::Task* taskPtr = 0;
            CCCompletionEvent completion;
            s_ccThread->postTask(createCCThreadTask(this, &CCThreadProxy::obtainBeginFrameAndCommitTaskFromCCThread, AllowCrossThreadAccess(&completion), AllowCrossThreadAccess(&taskPtr)));
            completion.wait();
            beginFrameAndCommitTask = adoptPtr(taskPtr);
        }

        beginFrameAndCommitTask->performTask();
    }

    bool success = false;
    CCCompletionEvent completion;
    s_ccThread->postTask(createCCThreadTask(this, &CCThreadProxy::drawLayersAndReadbackOnCCThread, AllowCrossThreadAccess(&completion), AllowCrossThreadAccess(&success), AllowCrossThreadAccess(pixels), rect));
    completion.wait();
    return success;
}
