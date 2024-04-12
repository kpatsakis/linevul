void V8Debugger::stepOverStatement()
{
    DCHECK(isPaused());
    DCHECK(!m_executionState.IsEmpty());
    v8::HandleScope handleScope(m_isolate);
    v8::Local<v8::Value> argv[] = { m_executionState };
    callDebuggerMethod("stepOverStatement", 1, argv);
    continueProgram();
}
