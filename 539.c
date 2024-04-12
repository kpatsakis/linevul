void AwContents::OnComputeScroll(JNIEnv* env,
                                 jobject obj,
                                 jlong animation_time_millis) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  browser_view_renderer_.OnComputeScroll(
      base::TimeTicks() +
      base::TimeDelta::FromMilliseconds(animation_time_millis));
}
