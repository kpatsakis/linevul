WebContentsImpl* WebContentsImpl::GetCreatedWindow(
    int process_id,
    int main_frame_widget_route_id) {
  auto key = std::make_pair(process_id, main_frame_widget_route_id);
  auto iter = pending_contents_.find(key);

  if (iter == pending_contents_.end())
    return nullptr;

  WebContentsImpl* new_contents = iter->second;
  pending_contents_.erase(key);
  RemoveDestructionObserver(new_contents);

  if (BrowserPluginGuest::IsGuest(new_contents))
    return new_contents;

  if (!new_contents->GetMainFrame()->GetProcess()->HasConnection() ||
      !new_contents->GetMainFrame()->GetView()) {
    return nullptr;
  }

  return new_contents;
}
