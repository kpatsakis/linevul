void PrintPreviewHandler::SendCloudPrintEnabled() {
  Profile* profile = Profile::FromBrowserContext(
      preview_web_contents()->GetBrowserContext());
  PrefService* prefs = profile->GetPrefs();
  if (prefs->GetBoolean(prefs::kCloudPrintSubmitEnabled)) {
    GURL gcp_url(CloudPrintURL(profile).GetCloudPrintServiceURL());
    base::StringValue gcp_url_value(gcp_url.spec());
    web_ui()->CallJavascriptFunction("setUseCloudPrint", gcp_url_value);
  }
}
