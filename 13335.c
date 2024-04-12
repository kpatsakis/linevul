void WorkerThread::shutdown()
{
    ASSERT(isCurrentThread());
    {
        MutexLocker lock(m_threadStateMutex);
        ASSERT(!m_shutdown);
        m_shutdown = true;
    }

    PlatformThreadData::current().threadTimers().setSharedTimer(nullptr);
    workerGlobalScope()->dispose();
    willDestroyIsolate();

    workerReportingProxy().willDestroyWorkerGlobalScope();

#if !ENABLE(OILPAN)
    ASSERT(m_workerGlobalScope->hasOneRef());
#endif
    m_workerGlobalScope->notifyContextDestroyed();
    m_workerGlobalScope = nullptr;

    backingThread().removeTaskObserver(m_microtaskRunner.get());
    backingThread().shutdown();
    destroyIsolate();

    m_microtaskRunner = nullptr;

    workerReportingProxy().workerThreadTerminated();

    m_terminationEvent->signal();

    PlatformThreadData::current().destroy();
}
