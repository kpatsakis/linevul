void Browser::SavePage() {
  UserMetrics::RecordAction(UserMetricsAction("SavePage"), profile_);
  TabContents* current_tab = GetSelectedTabContents();
  if (current_tab && current_tab->contents_mime_type() == "application/pdf")
    UserMetrics::RecordAction(UserMetricsAction("PDF.SavePage"), profile_);
  GetSelectedTabContentsWrapper()->download_tab_helper()->OnSavePage();
}
