NaClSubprocess* Plugin::LoadHelperNaClModule(nacl::DescWrapper* wrapper,
                                             const Manifest* manifest,
                                             ErrorInfo* error_info) {
  nacl::scoped_ptr<NaClSubprocess> nacl_subprocess(
      new NaClSubprocess("helper module", NULL, NULL));
  if (NULL == nacl_subprocess.get()) {
    error_info->SetReport(ERROR_SEL_LDR_INIT,
                          "unable to allocate helper subprocess.");
    return NULL;
  }

  if (!LoadNaClModuleCommon(wrapper, nacl_subprocess.get(), manifest,
                            false, error_info,
                            pp::BlockUntilComplete(),
                            pp::BlockUntilComplete())) {
    return NULL;
  }
  if (!nacl_subprocess->StartSrpcServices()) {
    error_info->SetReport(ERROR_SRPC_CONNECTION_FAIL,
                          "SRPC connection failure for " +
                          nacl_subprocess->description());
    return NULL;
  }

  PLUGIN_PRINTF(("Plugin::LoadHelperNaClModule (%s)\n",
                 nacl_subprocess.get()->detailed_description().c_str()));

  return nacl_subprocess.release();
}
