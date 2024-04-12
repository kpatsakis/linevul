LRESULT WebView::onWindowPositionChangedEvent(HWND, UINT, WPARAM, LPARAM lParam, bool& handled)
{
    if (reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_SHOWWINDOW)
        updateActiveStateSoon();

    handled = false;
    return 0;
}
