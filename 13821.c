void ForeignSessionHelper::FireForeignSessionCallback() {
  if (callback_.is_null())
    return;

  JNIEnv* env = AttachCurrentThread();
  Java_ForeignSessionCallback_onUpdated(env, callback_);
}
