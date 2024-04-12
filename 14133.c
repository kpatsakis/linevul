ScriptPromise ReadableStream::cancelInternal(ScriptState* scriptState, ScriptValue reason)
{
    setIsDisturbed();
    closeInternal();
    return m_source->cancelSource(scriptState, reason).then(ConstUndefined::create(scriptState));
}
