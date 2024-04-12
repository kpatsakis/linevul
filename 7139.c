void InspectorPageAgent::childDocumentOpened(Document* document)
{
    m_frontend->frameNavigated(buildObjectForFrame(document->frame()));
}
