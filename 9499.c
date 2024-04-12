void Plugin::NexeDidCrash(int32_t pp_error) {
  PLUGIN_PRINTF(("Plugin::NexeDidCrash (pp_error=%"NACL_PRId32")\n",
                 pp_error));
  if (pp_error != PP_OK) {
    PLUGIN_PRINTF(("Plugin::NexeDidCrash: CallOnMainThread callback with"
                   " non-PP_OK arg -- SHOULD NOT HAPPEN\n"));
  }
  PLUGIN_PRINTF(("Plugin::NexeDidCrash: crash event!\n"));
  int exit_status = main_subprocess_.service_runtime()->exit_status();
  if (-1 != exit_status) {
    PLUGIN_PRINTF((("Plugin::NexeDidCrash: nexe exited with status %d"
                    " so this is a \"controlled crash\".\n"),
                   exit_status));
  }
  if (nexe_error_reported()) {
    PLUGIN_PRINTF(("Plugin::NexeDidCrash: error already reported;"
                   " suppressing\n"));
    return;
  }
  if (nacl_ready_state() == DONE) {
    ReportDeadNexe();
  } else {
    ErrorInfo error_info;
    error_info.SetReport(ERROR_START_PROXY_CRASH,  // Not quite right.
                         "Nexe crashed during startup");
    ReportLoadError(error_info);
  }
}
