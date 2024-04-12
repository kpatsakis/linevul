inline void DialogHandler::dialogCreated(DOMWindow* dialogFrame)
{
    m_dialogContext = dialogFrame->frame() ? dialogFrame->frame()->script()->currentWorldContext() : v8::Local<v8::Context>();
    if (m_dialogContext.IsEmpty())
        return;
    if (m_dialogArguments.IsEmpty())
        return;
    v8::Context::Scope scope(m_dialogContext);
    m_dialogContext->Global()->Set(v8::String::NewSymbol("dialogArguments"), m_dialogArguments);
}
