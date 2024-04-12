void DevToolsWindow::OpenDevToolsWindowForWorker(
    Profile* profile,
    const scoped_refptr<DevToolsAgentHost>& worker_agent) {
  DevToolsWindow* window = FindDevToolsWindow(worker_agent.get());
  if (!window) {
    window = DevToolsWindow::CreateDevToolsWindowForWorker(profile);
    if (!window)
      return;
    window->bindings_->AttachTo(worker_agent);
  }
  window->ScheduleShow(DevToolsToggleAction::Show());
}
