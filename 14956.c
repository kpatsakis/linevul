ScriptPromise ReadableStreamReader::cancel(ScriptState* scriptState)
{
    return cancel(scriptState, ScriptValue(scriptState, v8::Undefined(scriptState->isolate())));
}
