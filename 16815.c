void Browser::ShowBrokenPageTab(TabContents* contents) {
  UserMetrics::RecordAction(UserMetricsAction("ReportBug"), profile_);
  string16 page_title = contents->GetTitle();
  NavigationEntry* entry = contents->controller().GetActiveEntry();
  if (!entry)
    return;
  std::string page_url = entry->url().spec();
  std::vector<std::string> subst;
  subst.push_back(UTF16ToASCII(page_title));
  subst.push_back(page_url);
  std::string report_page_url =
      ReplaceStringPlaceholders(kBrokenPageUrl, subst, NULL);
  ShowSingletonTab(GURL(report_page_url));
}
