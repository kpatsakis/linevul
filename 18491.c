void PrintPreviewDialogController::RemoveObservers(WebContents* contents) {
  registrar_.Remove(this, content::NOTIFICATION_WEB_CONTENTS_DESTROYED,
                    content::Source<WebContents>(contents));
  registrar_.Remove(this, content::NOTIFICATION_NAV_ENTRY_COMMITTED,
      content::Source<NavigationController>(&contents->GetController()));

  content::Source<content::RenderProcessHost> rph_source(
      contents->GetMainFrame()->GetProcess());
  if (registrar_.IsRegistered(this,
      content::NOTIFICATION_RENDERER_PROCESS_CLOSED, rph_source)) {
    if (host_contents_count_map_[contents->GetMainFrame()->GetProcess()] == 1) {
      registrar_.Remove(this, content::NOTIFICATION_RENDERER_PROCESS_CLOSED,
                        rph_source);
      host_contents_count_map_.erase(contents->GetMainFrame()->GetProcess());
    } else {
      --host_contents_count_map_[contents->GetMainFrame()->GetProcess()];
    }
  }
}
