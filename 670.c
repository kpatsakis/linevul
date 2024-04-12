void SafeBrowsingBlockingPage::RecordUserAction(BlockingPageEvent event) {
  DictionaryValue strings;
  PopulateMultipleThreatStringDictionary(&strings);

  string16 title;
  bool success = strings.GetString("title", &title);
  DCHECK(success);

  std::string action = "SBInterstitial";
  if (title ==
          l10n_util::GetStringUTF16(IDS_SAFE_BROWSING_MULTI_THREAT_TITLE)) {
    action.append("Multiple");
  } else if (title ==
                 l10n_util::GetStringUTF16(IDS_SAFE_BROWSING_MALWARE_TITLE)) {
    action.append("Malware");
  } else {
    DCHECK_EQ(title,
              l10n_util::GetStringUTF16(IDS_SAFE_BROWSING_PHISHING_TITLE));
    action.append("Phishing");
  }

  switch (event) {
    case SHOW:
      action.append("Show");
      break;
    case PROCEED:
      action.append("Proceed");
      break;
    case DONT_PROCEED:
      action.append("DontProceed");
      break;
    default:
      NOTREACHED() << "Unexpected event: " << event;
  }

  content::RecordComputedAction(action);
}
