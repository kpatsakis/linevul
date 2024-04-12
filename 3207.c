Plugin::~Plugin() {
  int64_t shutdown_start = NaClGetTimeOfDayMicroseconds();

  PLUGIN_PRINTF(("Plugin::~Plugin (this=%p, scriptable_plugin=%p)\n",
                 static_cast<void*>(this),
                 static_cast<void*>(scriptable_plugin())));
  pnacl_coordinator_.reset(NULL);
  if (ppapi_proxy_ != NULL) {
    HistogramTimeLarge(
        "NaCl.ModuleUptime.Normal",
        (shutdown_start - ready_time_) / NACL_MICROS_PER_MILLI);
  }

  url_downloaders_.erase(url_downloaders_.begin(), url_downloaders_.end());

  ShutdownProxy();
  ScriptablePlugin* scriptable_plugin_ = scriptable_plugin();
  ScriptablePlugin::Unref(&scriptable_plugin_);

  ShutDownSubprocesses();

  delete wrapper_factory_;
  delete[] argv_;
  delete[] argn_;

  HistogramTimeSmall(
      "NaCl.Perf.ShutdownTime.Total",
      (NaClGetTimeOfDayMicroseconds() - shutdown_start)
          / NACL_MICROS_PER_MILLI);

  PLUGIN_PRINTF(("Plugin::~Plugin (this=%p, return)\n",
                 static_cast<void*>(this)));
}
