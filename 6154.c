void TestingAutomationProvider::EnablePlugin(Browser* browser,
                                             DictionaryValue* args,
                                             IPC::Message* reply_message) {
  FilePath::StringType path;
  AutomationJSONReply reply(this, reply_message);
  if (!args->GetString("path", &path)) {
    reply.SendError("path not specified.");
  } else if (!PluginPrefs::GetForProfile(browser->profile())->EnablePlugin(
      true, FilePath(path))) {
    reply.SendError(StringPrintf("Could not enable plugin for path %s.",
                                 path.c_str()));
  } else {
    reply.SendSuccess(NULL);
  }
}
