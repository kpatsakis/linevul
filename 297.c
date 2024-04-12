  bool CaptureOnly(const Extension* extension, const GURL& url, int tab_id) {
    return !extension->permissions_data()->CanAccessPage(
               extension, url, url, tab_id, -1, NULL) &&
           extension->permissions_data()->CanCaptureVisiblePage(tab_id, NULL);
  }
