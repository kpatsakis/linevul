int RenderWidgetHostViewAndroid::GetNativeImeAdapter() {
  return reinterpret_cast<int>(&ime_adapter_android_);
}
