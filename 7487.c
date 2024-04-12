void RenderFrameHostImpl::SetCommitCallbackInterceptorForTesting(
    CommitCallbackInterceptor* interceptor) {
  DCHECK(!commit_callback_interceptor_ || !interceptor);
  commit_callback_interceptor_ = interceptor;
}
