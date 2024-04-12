void GpuProcessHost::InitOzone() {
  if (features::IsOzoneDrmMojo()) {
    auto interface_binder = base::BindRepeating(&GpuProcessHost::BindInterface,
                                                weak_ptr_factory_.GetWeakPtr());

    auto io_callback = base::BindOnce(
        [](const base::RepeatingCallback<void(const std::string&,
                                              mojo::ScopedMessagePipeHandle)>&
               interface_binder,
           ui::OzonePlatform* platform) {
          DCHECK_CURRENTLY_ON(BrowserThread::IO);
          platform->GetGpuPlatformSupportHost()->OnGpuServiceLaunched(
              BrowserThread::GetTaskRunnerForThread(BrowserThread::UI),
              BrowserThread::GetTaskRunnerForThread(BrowserThread::IO),
              interface_binder);
        },
        interface_binder);

    OzoneRegisterStartupCallbackHelper(std::move(io_callback));
  } else {
    auto send_callback = base::BindRepeating(&SendGpuProcessMessage,
                                             weak_ptr_factory_.GetWeakPtr());
    auto io_callback = base::BindOnce(
        [](int host_id,
           const base::RepeatingCallback<void(IPC::Message*)>& send_callback,
           ui::OzonePlatform* platform) {
          DCHECK_CURRENTLY_ON(BrowserThread::IO);
          platform->GetGpuPlatformSupportHost()->OnGpuProcessLaunched(
              host_id, BrowserThread::GetTaskRunnerForThread(BrowserThread::UI),
              BrowserThread::GetTaskRunnerForThread(BrowserThread::IO),
              send_callback);
        },
        host_id_, send_callback);
    OzoneRegisterStartupCallbackHelper(std::move(io_callback));
  }
}
