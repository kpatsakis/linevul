PepperRendererConnection::PepperRendererConnection(int render_process_id)
    : BrowserMessageFilter(kFilteredMessageClasses,
                           arraysize(kFilteredMessageClasses)),
      render_process_id_(render_process_id) {
  in_process_host_.reset(new BrowserPpapiHostImpl(this,
                                                  ppapi::PpapiPermissions(),
                                                  "",
                                                  base::FilePath(),
                                                  base::FilePath(),
                                                  true /* in_process */,
                                                  false /* external_plugin */));
}
