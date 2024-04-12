   scoped_refptr<UsbDeviceHandle> WaitForResult() {
     run_loop_.Run();
     return device_handle_;
   }
