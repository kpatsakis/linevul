void OnUpdated(const JavaRef<jobject>& java_callback,
               WebApkInstallResult result,
               bool relax_updates,
               const std::string& webapk_package) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_WebApkUpdateCallback_onResultFromNative(
      env, java_callback, static_cast<int>(result), relax_updates);
}
