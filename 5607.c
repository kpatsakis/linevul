static void Bitmap_prepareToDraw(JNIEnv* env, jobject, jlong bitmapHandle) {
 SkBitmap* bitmap = reinterpret_cast<SkBitmap*>(bitmapHandle);
    bitmap->lockPixels();
    bitmap->unlockPixels();
}
