void WorkerThread::terminateV8Execution()
{
    ASSERT(isMainThread());
    m_workerGlobalScope->script()->willScheduleExecutionTermination();
    v8::V8::TerminateExecution(m_isolate);
}
