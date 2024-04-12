float GetModernUIScaleWrapper() {
  float result = 1.0f;
  typedef float(WINAPI *GetModernUIScalePtr)(VOID);
  HMODULE lib = LoadLibraryA("metro_driver.dll");
  if (lib) {
    GetModernUIScalePtr func =
        reinterpret_cast<GetModernUIScalePtr>(
        GetProcAddress(lib, "GetModernUIScale"));
    if (func)
      result = func();
    FreeLibrary(lib);
  }
  return result;
}
