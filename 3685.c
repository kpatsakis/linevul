void RenderThreadImpl::OnDOMStorageEvent(
    const DOMStorageMsg_Event_Params& params) {
  if (!dom_storage_event_dispatcher_.get()) {
    EnsureWebKitInitialized();
    dom_storage_event_dispatcher_.reset(WebStorageEventDispatcher::create());
  }
  dom_storage_event_dispatcher_->dispatchStorageEvent(params.key,
      params.old_value, params.new_value, params.origin, params.page_url,
      params.namespace_id == dom_storage::kLocalStorageNamespaceId);
}
