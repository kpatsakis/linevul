void OfflineLoadPage::Show(int process_host_id, int render_view_id,
                           const GURL& url, Delegate* delegate) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  if (NetworkStateNotifier::is_connected()) {
    delegate->OnBlockingPageComplete(true);
  } else {
    TabContents* tab_contents =
        tab_util::GetTabContentsByID(process_host_id, render_view_id);
    if (!tab_contents)
      return;
    (new OfflineLoadPage(tab_contents, url, delegate))->Show();
  }
}
