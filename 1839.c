WebContentsImpl::GetJavaWebContents() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  WebContentsAndroid* web_contents_android =
      static_cast<WebContentsAndroid*>(GetUserData(kWebContentsAndroidKey));
  if (!web_contents_android) {
    web_contents_android = new WebContentsAndroid(this);
    SetUserData(kWebContentsAndroidKey, web_contents_android);
  }
  return web_contents_android->GetJavaObject();
}
