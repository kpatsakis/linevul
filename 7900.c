void AwContents::RequestGeolocationPermission(
    const GURL& origin,
    const base::Callback<void(bool)>& callback) {
  JNIEnv* env = AttachCurrentThread();
  ScopedJavaLocalRef<jobject> obj = java_ref_.get(env);
  if (obj.is_null())
    return;

  if (Java_AwContents_useLegacyGeolocationPermissionAPI(env, obj.obj())) {
    ShowGeolocationPrompt(origin, callback);
    return;
  }
  permission_request_handler_->SendRequest(
      scoped_ptr<AwPermissionRequestDelegate>(new SimplePermissionRequest(
          origin, AwPermissionRequest::Geolocation, callback)));
}
