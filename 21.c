scoped_refptr<base::TaskRunner> RenderThreadImpl::GetFileThreadTaskRunner() {
  return blink_platform_impl_->BaseFileTaskRunner();
}
