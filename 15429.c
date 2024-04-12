void HeadlessWebContentsImpl::Close() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  browser_context()->DestroyWebContents(this);
}
