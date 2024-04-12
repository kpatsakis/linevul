static void AdjustLinuxOOMScore(const std::string& process_type) {
  const int kMiscScore = 7;
  const int kPluginScore = 10;
  int score = -1;

  if (process_type == switches::kPluginProcess) {
    score = kPluginScore;
  } else if (process_type == switches::kUtilityProcess ||
             process_type == switches::kWorkerProcess ||
             process_type == switches::kGpuProcess ||
             process_type == switches::kServiceProcess) {
    score = kMiscScore;
  } else if (process_type == switches::kProfileImportProcess) {
    NOTIMPLEMENTED();
#ifndef DISABLE_NACL
  } else if (process_type == switches::kNaClLoaderProcess) {
    score = kPluginScore;
#endif
  } else if (process_type == switches::kZygoteProcess ||
             process_type.empty()) {
  } else if (process_type == switches::kExtensionProcess ||
             process_type == switches::kRendererProcess) {
    LOG(WARNING) << "process type '" << process_type << "' "
                 << "should go through the zygote.";
    return;
  } else {
    NOTREACHED() << "Unknown process type";
  }
  if (score > -1)
    base::AdjustOOMScore(base::GetCurrentProcId(), score);
}
