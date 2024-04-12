void OomInterventionImpl::ReportMemoryStats(
    OomInterventionMetrics& current_memory) {
  UMA_HISTOGRAM_MEMORY_MB(
      "Memory.Experimental.OomIntervention.RendererBlinkUsage",
      current_memory.current_blink_usage_kb / 1024);
  UMA_HISTOGRAM_MEMORY_LARGE_MB(
      "Memory.Experimental.OomIntervention."
      "RendererPrivateMemoryFootprint",
      current_memory.current_private_footprint_kb / 1024);
  UMA_HISTOGRAM_MEMORY_MB(
      "Memory.Experimental.OomIntervention.RendererSwapFootprint",
      current_memory.current_swap_kb / 1024);
  UMA_HISTOGRAM_MEMORY_LARGE_MB(
      "Memory.Experimental.OomIntervention.RendererVmSize",
      current_memory.current_vm_size_kb / 1024);

  CrashMemoryMetricsReporterImpl::Instance().WriteIntoSharedMemory(
      current_memory);
}
