void WebPage::selectAll()
{
    if (d->m_page->defersLoading())
        return;
    d->m_inputHandler->selectAll();
}
