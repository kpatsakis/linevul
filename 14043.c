static void SetForceAuxiliaryBitmapRendering(
    JNIEnv* env,
    const JavaParamRef<jclass>&,
    jboolean force_auxiliary_bitmap_rendering) {
  g_force_auxiliary_bitmap_rendering = force_auxiliary_bitmap_rendering;
}
