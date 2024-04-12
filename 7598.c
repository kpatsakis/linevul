MetricsWebContentsObserver::TestingObserver::TestingObserver(
    content::WebContents* web_contents)
    : observer_(page_load_metrics::MetricsWebContentsObserver::FromWebContents(
          web_contents)) {
  observer_->AddTestingObserver(this);
}
