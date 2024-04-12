RenderProcessHostImpl::~RenderProcessHostImpl() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
#ifndef NDEBUG
  DCHECK(is_self_deleted_)
      << "RenderProcessHostImpl is destroyed by something other than itself";
#endif

  in_process_renderer_.reset();

  ChildProcessSecurityPolicyImpl::GetInstance()->Remove(GetID());

  if (gpu_observer_registered_) {
    ui::GpuSwitchingManager::GetInstance()->RemoveObserver(this);
    gpu_observer_registered_ = false;
  }

  is_dead_ = true;

  UnregisterHost(GetID());

  if (!base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kDisableGpuShaderDiskCache)) {
    BrowserThread::PostTask(BrowserThread::IO, FROM_HERE,
                            base::Bind(&RemoveShaderInfo, GetID()));
  }
}
