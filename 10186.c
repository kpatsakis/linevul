void WebPage::setComposition(const String& compositionString, const Vector<WebCore::CompositionUnderline>& underlines, uint64_t cursorPosition)
{
    Frame* frame = m_page->focusController()->focusedOrMainFrame();
    if (!frame || !frame->editor()->canEdit())
        return;
    frame->editor()->setComposition(compositionString, underlines, cursorPosition, 0);
}
