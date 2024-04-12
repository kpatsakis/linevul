void WebPageProxy::getMenuBarIsVisible(bool& menuBarIsVisible)
{
    menuBarIsVisible = m_uiClient.menuBarIsVisible(this);
}
