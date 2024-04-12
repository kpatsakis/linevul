void Browser::JSOutOfMemoryHelper(WebContents* web_contents) {
  InfoBarTabHelper* infobar_helper =
      InfoBarTabHelper::FromWebContents(web_contents);
  if (!infobar_helper)
    return;

  infobar_helper->AddInfoBar(new SimpleAlertInfoBarDelegate(
      infobar_helper,
      NULL,
      l10n_util::GetStringUTF16(IDS_JS_OUT_OF_MEMORY_PROMPT),
      true));
}
