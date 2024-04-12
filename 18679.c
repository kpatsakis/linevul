void V8WindowShell::namedItemAdded(HTMLDocument* document, const AtomicString& name)
{
    ASSERT(m_world->isMainWorld());

    if (m_context.isEmpty())
        return;

    v8::HandleScope handleScope(m_isolate);
    v8::Context::Scope contextScope(m_context.newLocal(m_isolate));

    ASSERT(!m_document.isEmpty());
    v8::Handle<v8::Object> documentHandle = m_document.newLocal(m_isolate);
    checkDocumentWrapper(documentHandle, document);
    documentHandle->SetAccessor(v8String(name, m_isolate), getter);
}
