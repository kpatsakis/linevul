void DownloadItemImpl::ShowDownloadInShell() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  content::GetContentClient()->browser()->ShowItemInFolder(GetFullPath());
}
