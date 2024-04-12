void WebPageProxy::startDragDrop(const IntPoint& imageOrigin, const IntPoint& dragPoint, uint64_t okEffect, 
    const HashMap<UINT, Vector<String> >& dataMap, const IntSize& dragImageSize, const SharedMemory::Handle& dragImageHandle, bool isLinkDrag)
{
    COMPtr<WCDataObject> dataObject;
    WCDataObject::createInstance(&dataObject, dataMap);

    RefPtr<SharedMemory> memoryBuffer = SharedMemory::create(dragImageHandle, SharedMemory::ReadOnly);
    if (!memoryBuffer)
        return;

    RefPtr<WebDragSource> source = WebDragSource::createInstance();
    if (!source)
        return;

    COMPtr<IDragSourceHelper> helper;
    if (FAILED(::CoCreateInstance(CLSID_DragDropHelper, 0, CLSCTX_INPROC_SERVER, IID_IDragSourceHelper, reinterpret_cast<LPVOID*>(&helper))))
        return;

    BitmapInfo bitmapInfo = BitmapInfo::create(dragImageSize);
    void* bits;
    OwnPtr<HBITMAP> hbmp(::CreateDIBSection(0, &bitmapInfo, DIB_RGB_COLORS, &bits, 0, 0));
    memcpy(bits, memoryBuffer->data(), memoryBuffer->size());

    SHDRAGIMAGE sdi;
    sdi.sizeDragImage.cx = bitmapInfo.bmiHeader.biWidth;
    sdi.sizeDragImage.cy = bitmapInfo.bmiHeader.biHeight;
    sdi.crColorKey = 0xffffffff;
    sdi.hbmpDragImage = hbmp.leakPtr();
    sdi.ptOffset.x = dragPoint.x() - imageOrigin.x();
    sdi.ptOffset.y = dragPoint.y() - imageOrigin.y();
    if (isLinkDrag)
        sdi.ptOffset.y = bitmapInfo.bmiHeader.biHeight - sdi.ptOffset.y;

    helper->InitializeFromBitmap(&sdi, dataObject.get());

    DWORD effect = DROPEFFECT_NONE;

    DragOperation operation = DragOperationNone;
    if (::DoDragDrop(dataObject.get(), source.get(), okEffect, &effect) == DRAGDROP_S_DROP) {
        if (effect & DROPEFFECT_COPY)
            operation = DragOperationCopy;
        else if (effect & DROPEFFECT_LINK)
            operation = DragOperationLink;
        else if (effect & DROPEFFECT_MOVE)
            operation = DragOperationMove;
    }
    POINT globalPoint;
    ::GetCursorPos(&globalPoint);
    POINT localPoint = globalPoint;
    ::ScreenToClient(m_pageClient->nativeWindow(), &localPoint);

    dragEnded(localPoint, globalPoint, operation);
}
