void RenderFrameDevToolsAgentHost::WasShown() {
#if defined(OS_ANDROID)
  GetWakeLock()->RequestWakeLock();
#endif
}
