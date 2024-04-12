ULONG STDMETHODCALLTYPE WebView::AddRef(void)
{
    ref();
    return refCount();
}
