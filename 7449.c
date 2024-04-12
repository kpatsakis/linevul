void V8Debugger::disable()
{
    if (--m_enableCount)
        return;
    DCHECK(enabled());
    clearBreakpoints();
    m_debuggerScript.Reset();
    m_debuggerContext.Reset();
    allAsyncTasksCanceled();
    v8::Debug::SetDebugEventListener(m_isolate, nullptr);
}
