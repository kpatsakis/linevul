void WebContentsImpl::OnPepperPluginHung(RenderFrameHostImpl* source,
                                         int plugin_child_id,
                                         const base::FilePath& path,
                                         bool is_hung) {
  UMA_HISTOGRAM_COUNTS("Pepper.PluginHung", 1);

  for (auto& observer : observers_)
    observer.PluginHungStatusChanged(plugin_child_id, path, is_hung);
}
