void DevToolsUIBindings::DocumentOnLoadCompletedInMainFrame() {
#if !BUILDFLAG(DEBUG_DEVTOOLS)
  FrontendLoaded();
#endif
}
