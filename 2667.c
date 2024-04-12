void BrowserContextDelegateTraits::Destruct(const BrowserContextDelegate* x) {
  if (content::BrowserThread::CurrentlyOn(content::BrowserThread::UI)) {
    delete x;
    return;
  }

  if (!content::BrowserThread::DeleteSoon(content::BrowserThread::UI,
                                          FROM_HERE, x)) {
    LOG(ERROR) <<
        "BrowserContextDelegate won't be deleted. This could be due to it "
        "being leaked until after Chromium shutdown has begun";
  }
}
