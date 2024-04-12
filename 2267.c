  MockPluginProcessHostClient(ResourceContext* context, bool expect_fail)
      : context_(context),
        channel_(NULL),
        set_plugin_info_called_(false),
        expect_fail_(expect_fail) {
  }
