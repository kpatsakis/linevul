void WebView::startTrackingMouseLeave()
{
    if (m_trackingMouseLeave)
        return;
    m_trackingMouseLeave = true;

    TRACKMOUSEEVENT trackMouseEvent;
    trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
    trackMouseEvent.dwFlags = TME_LEAVE;
    trackMouseEvent.hwndTrack = m_window;

    ::TrackMouseEvent(&trackMouseEvent);
}
