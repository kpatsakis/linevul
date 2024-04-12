void AutofillDownloadManager::SetPositiveUploadRate(double rate) {
  if (rate == positive_upload_rate_)
    return;
  positive_upload_rate_ = rate;
  DCHECK_GE(rate, 0.0);
  DCHECK_LE(rate, 1.0);
  DCHECK(profile_);
  PrefService* preferences = profile_->GetPrefs();
  preferences->SetDouble(prefs::kAutofillPositiveUploadRate, rate);
}
