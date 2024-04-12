   void SetResult(scoped_refptr<UsbDeviceHandle> device_handle) {
     device_handle_ = device_handle;
     run_loop_.Quit();
   }
