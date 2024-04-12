static jboolean Region_isEmpty(JNIEnv* env, jobject region) {
 bool result = GetSkRegion(env, region)->isEmpty();
 return boolTojboolean(result);
}
