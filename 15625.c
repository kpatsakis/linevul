jlong AwContents::GetAwDrawGLViewContext(JNIEnv* env, jobject obj) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return reinterpret_cast<intptr_t>(
      browser_view_renderer_.GetAwDrawGLViewContext());
}
