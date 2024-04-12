  bool AllowedScript(const Extension* extension, const GURL& url,
                     const GURL& top_url) {
    return AllowedScript(extension, url, top_url, -1);
  }
