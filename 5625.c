    DeferredTaskPopupListSelectMultiple(WebPagePrivate* webPagePrivate, int size, const bool* selecteds)
        : DeferredTaskType(webPagePrivate)
    {
        webPagePrivate->m_cachedPopupListSelecteds.append(selecteds, size);
    }
