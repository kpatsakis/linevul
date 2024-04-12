void AwContents::ClearMatches(JNIEnv* env, jobject obj) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  GetFindHelper()->ClearMatches();
}
