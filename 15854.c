void AwContents::ShowGeolocationPrompt(const GURL& requesting_frame,
                                       base::Callback<void(bool)> callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  GURL origin = requesting_frame.GetOrigin();
  bool show_prompt = pending_geolocation_prompts_.empty();
  pending_geolocation_prompts_.push_back(OriginCallback(origin, callback));
  if (show_prompt) {
    ShowGeolocationPromptHelper(java_ref_, origin);
  }
}
