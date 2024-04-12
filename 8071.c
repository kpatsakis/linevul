void V8Debugger::asyncTaskCanceled(void* task)
{
    if (!m_maxAsyncCallStackDepth)
        return;
    m_asyncTaskStacks.erase(task);
    m_recurringTasks.erase(task);
}
