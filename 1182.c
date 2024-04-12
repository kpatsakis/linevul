static bool DeviceScaleEnsuresTextQuality(float device_scale_factor) {
#if defined(OS_ANDROID) || defined(OS_CHROMEOS)
  return true;
#else
  return device_scale_factor >= 1.5f;
#endif
}
