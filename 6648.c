void WebPageProxy::backForwardRemovedItem(uint64_t itemID)
{
    process()->send(Messages::WebPage::DidRemoveBackForwardItem(itemID), m_pageID);
}
