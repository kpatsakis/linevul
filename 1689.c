static void Region_destructor(JNIEnv* env, jobject, jlong regionHandle) {
 SkRegion* region = reinterpret_cast<SkRegion*>(regionHandle);
 SkASSERT(region);
 delete region;
}
