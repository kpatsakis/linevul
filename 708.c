void Browser::ShowSingletonTab(const GURL& url, bool ignore_path) {
  browser::NavigateParams params(this, url, PageTransition::AUTO_BOOKMARK);
  params.disposition = SINGLETON_TAB;
  params.show_window = true;
  params.ignore_path = ignore_path;
  browser::Navigate(&params);
}
