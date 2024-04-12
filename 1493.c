void ChromeRenderMessageFilter::OnCanTriggerClipboardRead(
    const GURL& origin, bool* allowed) {
  *allowed = extension_info_map_->SecurityOriginHasAPIPermission(
      origin, render_process_id_, ExtensionAPIPermission::kClipboardRead);
}
