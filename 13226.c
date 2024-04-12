void Document::setSelectedStylesheetSet(const String& aString)
{
    m_styleSheetCollection->setSelectedStylesheetSetName(aString);
    styleResolverChanged(DeferRecalcStyle);
}
