BrowserPpapiHost* BrowserPpapiHost::CreateExternalPluginProcess(
    IPC::Sender* sender,
    ppapi::PpapiPermissions permissions,
    base::ProcessHandle plugin_child_process,
    IPC::ChannelProxy* channel,
    int render_process_id,
    int render_view_id,
    const base::FilePath& profile_directory) {
  BrowserPpapiHostImpl* browser_ppapi_host =
      new BrowserPpapiHostImpl(sender,
                               permissions,
                               std::string(),
                               base::FilePath(),
                               profile_directory,
                               false /* in_process */,
                               true /* external_plugin */);
  browser_ppapi_host->set_plugin_process(
      base::Process::DeprecatedGetProcessFromHandle(plugin_child_process));

  scoped_refptr<PepperMessageFilter> pepper_message_filter(
      new PepperMessageFilter());
  channel->AddFilter(pepper_message_filter->GetFilter());
  channel->AddFilter(browser_ppapi_host->message_filter().get());
  channel->AddFilter((new TraceMessageFilter(render_process_id))->GetFilter());

  return browser_ppapi_host;
}
