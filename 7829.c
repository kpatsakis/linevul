void FrameView::addSlowRepaintObject()
{
    if (!m_slowRepaintObjectCount++) {
        if (Page* page = m_frame->page()) {
            if (ScrollingCoordinator* scrollingCoordinator = page->scrollingCoordinator())
                scrollingCoordinator->frameViewHasSlowRepaintObjectsDidChange(this);
        }
    }
}
