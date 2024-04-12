void BrowserWindowGtk::UpdateDevTools() {
  UpdateDevToolsForContents(chrome::GetActiveWebContents(browser_.get()));
}
