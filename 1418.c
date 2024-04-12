static void Bitmap_destructor(JNIEnv* env, jobject, jlong bitmapHandle) {
 SkBitmap* bitmap = reinterpret_cast<SkBitmap*>(bitmapHandle);
#ifdef USE_OPENGL_RENDERER
 if (android::uirenderer::ResourceCache::hasInstance()) {
        android::uirenderer::ResourceCache::getInstance().destructor(bitmap);
 return;
 }
#endif // USE_OPENGL_RENDERER
 delete bitmap;
}
