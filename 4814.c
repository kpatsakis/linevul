void WebPageProxy::didChangeBackForwardList(WebBackForwardListItem* added, Vector<RefPtr<APIObject> >* removed)
{
    m_loaderClient.didChangeBackForwardList(this, added, removed);
}
