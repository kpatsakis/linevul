  bool IsBlocked(const scoped_refptr<const Extension>& extension,
                 const GURL& url,
                 int tab_id) {
    return IsAllowed(extension, url, PERMITTED_NONE, tab_id);
  }
