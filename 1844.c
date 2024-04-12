jlong AwContents::CapturePicture(JNIEnv* env,
                                 jobject obj,
                                 int width,
                                 int height) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return reinterpret_cast<intptr_t>(
      new AwPicture(browser_view_renderer_.CapturePicture(width, height)));
}
