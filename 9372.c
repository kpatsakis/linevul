void AutomationProviderImportSettingsObserver::ImportEnded() {
  if (provider_)
    AutomationJSONReply(provider_, reply_message_.release()).SendSuccess(NULL);
  delete this;
}
