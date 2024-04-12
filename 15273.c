scoped_refptr<base::MessageLoopProxy> RenderThreadImpl::GetIOLoopProxy() {
  return ChildProcess::current()->io_message_loop_proxy();
}
