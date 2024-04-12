void UsbDeviceImpl::Opened(PlatformUsbDeviceHandle platform_handle,
                           const OpenCallback& callback) {
  DCHECK(thread_checker_.CalledOnValidThread());
  scoped_refptr<UsbDeviceHandleImpl> device_handle = new UsbDeviceHandleImpl(
      context_, this, platform_handle, blocking_task_runner_);
  handles_.push_back(device_handle);
  callback.Run(device_handle);
}
