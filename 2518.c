bool InitializeSDK() {
  SetUpV8();

  FPDF_LIBRARY_CONFIG config;
  config.version = 2;
  config.m_pUserFontPaths = nullptr;
  config.m_pIsolate = v8::Isolate::GetCurrent();
  config.m_v8EmbedderSlot = gin::kEmbedderPDFium;
  FPDF_InitLibraryWithConfig(&config);

#if defined(OS_LINUX)
  FPDF_SetSystemFontInfo(&g_font_info);
#endif

  FSDK_SetUnSpObjProcessHandler(&g_unsupported_info);

  return true;
}
