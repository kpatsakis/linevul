void DialogHandler::dialogCreated(LocalDOMWindow* dialogFrame)
{
    if (m_dialogArguments.IsEmpty())
        return;
    v8::Handle<v8::Context> context = toV8Context(dialogFrame->frame(), m_scriptState->world());
    if (context.IsEmpty())
        return;
    m_scriptStateForDialogFrame = ScriptState::from(context);

    ScriptState::Scope scope(m_scriptStateForDialogFrame.get());
    m_scriptStateForDialogFrame->context()->Global()->Set(v8AtomicString(m_scriptState->isolate(), "dialogArguments"), m_dialogArguments);
}
