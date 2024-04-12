void V8Debugger::handleV8DebugEvent(const v8::Debug::EventDetails& eventDetails)
{
    if (!enabled())
        return;
    v8::DebugEvent event = eventDetails.GetEvent();
    if (event != v8::AsyncTaskEvent && event != v8::Break && event != v8::Exception && event != v8::AfterCompile && event != v8::BeforeCompile && event != v8::CompileError)
        return;

    v8::Local<v8::Context> eventContext = eventDetails.GetEventContext();
    DCHECK(!eventContext.IsEmpty());

    if (event == v8::AsyncTaskEvent) {
        v8::HandleScope scope(m_isolate);
        handleV8AsyncTaskEvent(eventContext, eventDetails.GetExecutionState(), eventDetails.GetEventData());
        return;
    }

    V8DebuggerAgentImpl* agent = m_inspector->enabledDebuggerAgentForGroup(getGroupId(eventContext));
    if (agent) {
        v8::HandleScope scope(m_isolate);
        if (m_ignoreScriptParsedEventsCounter == 0 && (event == v8::AfterCompile || event == v8::CompileError)) {
            v8::Context::Scope contextScope(debuggerContext());
            v8::Local<v8::Value> argv[] = { eventDetails.GetEventData() };
            v8::Local<v8::Value> value = callDebuggerMethod("getAfterCompileScript", 1, argv).ToLocalChecked();
            if (value->IsNull())
                return;
            DCHECK(value->IsObject());
            v8::Local<v8::Object> scriptObject = v8::Local<v8::Object>::Cast(value);
            agent->didParseSource(wrapUnique(new V8DebuggerScript(m_isolate, scriptObject, inLiveEditScope)), event == v8::AfterCompile);
        } else if (event == v8::Exception) {
            v8::Local<v8::Object> eventData = eventDetails.GetEventData();
            v8::Local<v8::Value> exception = callInternalGetterFunction(eventData, "exception");
            v8::Local<v8::Value> promise = callInternalGetterFunction(eventData, "promise");
            bool isPromiseRejection = !promise.IsEmpty() && promise->IsObject();
            handleProgramBreak(eventContext, eventDetails.GetExecutionState(), exception, v8::Local<v8::Array>(), isPromiseRejection);
        } else if (event == v8::Break) {
            v8::Local<v8::Value> argv[] = { eventDetails.GetEventData() };
            v8::Local<v8::Value> hitBreakpoints = callDebuggerMethod("getBreakpointNumbers", 1, argv).ToLocalChecked();
            DCHECK(hitBreakpoints->IsArray());
            handleProgramBreak(eventContext, eventDetails.GetExecutionState(), v8::Local<v8::Value>(), hitBreakpoints.As<v8::Array>());
        }
    }
}
