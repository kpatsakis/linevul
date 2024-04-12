void RenderViewImpl::OnUpdateWebPreferences(const WebPreferences& prefs) {
  webkit_preferences_ = prefs;
  ApplyWebPreferencesInternal(webkit_preferences_, webview(), compositor_deps_);
}
