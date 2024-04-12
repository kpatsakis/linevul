WebContentsImpl::GetJavaWebContents() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return GetWebContentsAndroid()->GetJavaObject();
}
