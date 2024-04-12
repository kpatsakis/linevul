void AllViewsStoppedLoadingObserver::OnFirstPendingLoad(
    content::WebContents* web_contents) {
  pending_tabs_.insert(web_contents);
}
