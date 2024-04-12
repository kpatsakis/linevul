void DevToolsUIBindings::PerformActionOnRemotePage(const std::string& page_id,
                                                   const std::string& action) {
  if (!remote_targets_handler_)
    return;
  scoped_refptr<content::DevToolsAgentHost> host =
      remote_targets_handler_->GetTarget(page_id);
  if (!host)
    return;
  if (action == kRemotePageActionInspect)
    delegate_->Inspect(host);
  else if (action == kRemotePageActionReload)
    host->Reload();
  else if (action == kRemotePageActionActivate)
    host->Activate();
  else if (action == kRemotePageActionClose)
    host->Close();
}
