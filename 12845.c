  ExtensionsQuotaServiceTest()
      : extension_a_("a"),
        extension_b_("b"),
        extension_c_("c"),
        loop_(),
        ui_thread_(BrowserThread::UI, &loop_) {
  }
