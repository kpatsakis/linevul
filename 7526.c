void WebView::windowAncestryDidChange()
{
    HWND newTopLevelParentWindow;
    if (m_window)
        newTopLevelParentWindow = findTopLevelParentWindow(m_window);
    else {
        newTopLevelParentWindow = 0;
    }

    if (newTopLevelParentWindow == m_topLevelParentWindow)
        return;

    if (m_topLevelParentWindow)
        WindowMessageBroadcaster::removeListener(m_topLevelParentWindow, this);

    m_topLevelParentWindow = newTopLevelParentWindow;

    if (m_topLevelParentWindow)
        WindowMessageBroadcaster::addListener(m_topLevelParentWindow, this);

    updateActiveState();
}
