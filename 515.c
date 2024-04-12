void Document::setSelectedStylesheetSet(const String& aString)
{
    m_styleEngine->setSelectedStylesheetSetName(aString);
    styleResolverChanged(RecalcStyleDeferred);
}
