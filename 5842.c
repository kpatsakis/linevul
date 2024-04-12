void PlatformSensorAndroid::StopSensor() {
  JNIEnv* env = AttachCurrentThread();
  Java_PlatformSensor_stopSensor(env, j_object_);
}
