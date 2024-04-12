ChromeContentBrowserClient::GetExtraServiceManifests() {
  return std::vector<service_manager::Manifest> {
    GetChromeRendererManifest(),
#if BUILDFLAG(ENABLE_NACL)
        GetNaClLoaderManifest(),
#if defined(OS_WIN) && defined(ARCH_CPU_X86)
        GetNaClBrokerManifest(),
#endif  // defined(OS_WIN)
#endif  // BUILDFLAG(ENABLE_NACL)
  };
}
