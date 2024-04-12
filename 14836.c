void Document::registerNodeList(LiveNodeListBase* list)
{
    if (list->hasIdNameCache())
        m_nodeListCounts[InvalidateOnIdNameAttrChange]++;
    m_nodeListCounts[list->invalidationType()]++;
    if (list->isRootedAtDocument())
        m_listsInvalidatedAtDocument.add(list);
}
