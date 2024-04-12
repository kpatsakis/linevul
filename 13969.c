void AutofillDownloadManager::SetNegativeUploadRate(double rate) {
  if (rate == negative_upload_rate_)
    return;
  negative_upload_rate_ = rate;
  DCHECK_GE(rate, 0.0);
  DCHECK_LE(rate, 1.0);
  DCHECK(profile_);
  PrefService* preferences = profile_->GetPrefs();
  preferences->SetDouble(prefs::kAutofillNegativeUploadRate, rate);
}
