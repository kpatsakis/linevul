void DevToolsWindow::Inspect(scoped_refptr<content::DevToolsAgentHost> host) {
  DevToolsWindow::OpenDevToolsWindow(host, profile_);
}
