void ChromeHttpAuthHandler::SetAuth(JNIEnv* env,
                                    const JavaParamRef<jobject>&,
                                    const JavaParamRef<jstring>& username,
                                    const JavaParamRef<jstring>& password) {
  if (observer_) {
    base::string16 username16 = ConvertJavaStringToUTF16(env, username);
    base::string16 password16 = ConvertJavaStringToUTF16(env, password);
    observer_->SetAuth(username16, password16);
  }
}
