void ChromeRenderMessageFilter::OnGetExtensionMessageBundleOnFileThread(
    const FilePath& extension_path,
    const std::string& extension_id,
    const std::string& default_locale,
    IPC::Message* reply_msg) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::FILE));

  scoped_ptr<ExtensionMessageBundle::SubstitutionMap> dictionary_map(
      extension_file_util::LoadExtensionMessageBundleSubstitutionMap(
          extension_path,
          extension_id,
          default_locale));

  ExtensionHostMsg_GetMessageBundle::WriteReplyParams(
      reply_msg, *dictionary_map);
  Send(reply_msg);
}
