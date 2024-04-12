void WorkerThread::stop()
{
    SafePointScope safePointScope(ThreadState::HeapPointersOnStack);
    stopInternal();
}
