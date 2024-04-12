void TestingAutomationProvider::SaveTabContents(
    Browser* browser,
    DictionaryValue* args,
    IPC::Message* reply_message) {
  int tab_index = 0;
  FilePath::StringType filename;
  FilePath::StringType parent_directory;
  WebContents* web_contents = NULL;

  if (!args->GetInteger("tab_index", &tab_index) ||
      !args->GetString("filename", &filename)) {
    AutomationJSONReply(this, reply_message)
        .SendError("tab_index or filename param missing");
    return;
  } else {
    web_contents = browser->GetWebContentsAt(tab_index);
    if (!web_contents) {
      AutomationJSONReply(this, reply_message).SendError("no tab at tab_index");
      return;
    }
  }
  parent_directory = FilePath(filename).DirName().value();
  if (!web_contents->SavePage(
          FilePath(filename),
          FilePath(parent_directory),
          SavePackage::SAVE_AS_ONLY_HTML)) {
    AutomationJSONReply(this, reply_message).SendError(
        "Could not initiate SavePage");
    return;
  }
  new SavePackageNotificationObserver(
      DownloadServiceFactory::GetForProfile(
          browser->profile())->GetDownloadManager(),
      this, reply_message);
}
