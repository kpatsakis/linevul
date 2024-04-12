void ChromeContentClient::SetGpuInfo(const content::GPUInfo& gpu_info) {
  child_process_logging::SetGpuInfo(gpu_info);
}
