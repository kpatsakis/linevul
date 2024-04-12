void GpuProcessHost::RequestGPUInfo(RequestGPUInfoCallback request_cb) {
  if (status_ == SUCCESS || status_ == FAILURE) {
    std::move(request_cb).Run(GpuDataManagerImpl::GetInstance()->GetGPUInfo());
    return;
  }

  request_gpu_info_callbacks_.push_back(std::move(request_cb));
}
