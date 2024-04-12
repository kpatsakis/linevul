void Browser::OpenPrivacyDashboardTabAndActivate() {
  OpenURL(GURL(kPrivacyDashboardUrl), GURL(),
          NEW_FOREGROUND_TAB, PageTransition::LINK);
  window_->Activate();
}
