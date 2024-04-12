void WebView::updateActiveStateSoon()
{

    ::SetTimer(m_window, UpdateActiveStateTimer, 0, 0);
}
