void DisplayItemList::replay(GraphicsContext& context)
{
    TRACE_EVENT0("blink,benchmark", "DisplayItemList::replay");
    ASSERT(m_newDisplayItems.isEmpty());
    for (DisplayItem& displayItem : m_currentDisplayItems)
        displayItem.replay(context);
}
