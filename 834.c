void AwContents::OnReceivedIcon(const GURL& icon_url, const SkBitmap& bitmap) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  JNIEnv* env = AttachCurrentThread();
  ScopedJavaLocalRef<jobject> obj = java_ref_.get(env);
  if (obj.is_null())
    return;

  content::NavigationEntry* entry =
      web_contents_->GetController().GetLastCommittedEntry();

  if (entry) {
    entry->GetFavicon().valid = true;
    entry->GetFavicon().url = icon_url;
    entry->GetFavicon().image = gfx::Image::CreateFrom1xBitmap(bitmap);
  }

  Java_AwContents_onReceivedIcon(
      env, obj.obj(), gfx::ConvertToJavaBitmap(&bitmap).obj());
}
