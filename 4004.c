WebContentsAndroid::GetJavaObject() {
  return base::android::ScopedJavaLocalRef<jobject>(obj_);
}
