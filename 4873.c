void Document::unregisterForPrivateBrowsingStateChangedCallbacks(Element* e)
{
    m_privateBrowsingStateChangedElements.remove(e);
}
