void CommandBufferProxyImpl::OnSwapBuffersCompleted(
    const SwapBuffersCompleteParams& params) {
  if (!swap_buffers_completion_callback_.is_null())
    swap_buffers_completion_callback_.Run(params);
}
