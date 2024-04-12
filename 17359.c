WebCore::DragOperation WebView::keyStateToDragOperation(DWORD grfKeyState) const
{
    if (!m_page)
        return DragOperationNone;

    DragOperation operation = m_page->dragOperation();

    if ((grfKeyState & (MK_CONTROL | MK_SHIFT)) == (MK_CONTROL | MK_SHIFT))
        operation = DragOperationLink;
    else if ((grfKeyState & MK_CONTROL) == MK_CONTROL)
        operation = DragOperationCopy;
    else if ((grfKeyState & MK_SHIFT) == MK_SHIFT)
        operation = DragOperationGeneric;

    return operation;
}
