bool RenderViewHostManager::ShouldReuseWebUI(
    const NavigationEntry* curr_entry,
    const NavigationEntryImpl* new_entry) const {
  NavigationControllerImpl& controller =
      delegate_->GetControllerForRenderManager();
  return curr_entry && web_ui_.get() &&
      (WebUIControllerFactoryRegistry::GetInstance()->GetWebUIType(
          controller.GetBrowserContext(), curr_entry->GetURL()) ==
       WebUIControllerFactoryRegistry::GetInstance()->GetWebUIType(
          controller.GetBrowserContext(), new_entry->GetURL()));
}
