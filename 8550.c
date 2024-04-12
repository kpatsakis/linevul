void AwContents::FindAllAsync(JNIEnv* env, jobject obj, jstring search_string) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  GetFindHelper()->FindAllAsync(ConvertJavaStringToUTF16(env, search_string));
}
