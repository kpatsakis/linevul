void TestingAutomationProvider::WaitForAllDownloadsToComplete(
    Browser* browser,
    DictionaryValue* args,
    IPC::Message* reply_message) {
  ListValue* pre_download_ids = NULL;

  if (!args->GetList("pre_download_ids", &pre_download_ids)) {
    AutomationJSONReply(this, reply_message)
        .SendError(StringPrintf("List of IDs of previous downloads required."));
    return;
  }

  DownloadService* download_service =
      DownloadServiceFactory::GetForProfile(browser->profile());
  if (!download_service->HasCreatedDownloadManager()) {
    AutomationJSONReply(this, reply_message).SendSuccess(NULL);
    return;
  }

  new AllDownloadsCompleteObserver(
      this, reply_message, download_service->GetDownloadManager(),
      pre_download_ids);
}
