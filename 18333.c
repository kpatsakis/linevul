    SynchronizeVisualPropertiesMessageFilter()
    : content::BrowserMessageFilter(kMessageClassesToFilter,
                                    arraysize(kMessageClassesToFilter)),
      screen_space_rect_run_loop_(std::make_unique<base::RunLoop>()),
      screen_space_rect_received_(false) {}
