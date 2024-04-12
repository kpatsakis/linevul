  virtual bool CheckBrowseUrl(const GURL& gurl, Client* client) {
    if (badurls[gurl.spec()] == SAFE)
      return true;

    BrowserThread::PostTask(
        BrowserThread::IO, FROM_HERE,
        base::Bind(&FakeSafeBrowsingService::OnCheckBrowseURLDone,
                   this, gurl, client));
    return false;
  }
