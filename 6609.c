ChromeDownloadDelegate::~ChromeDownloadDelegate() {
   JNIEnv* env = base::android::AttachCurrentThread();
   env->DeleteGlobalRef(java_ref_);
}
