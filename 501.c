void GLSurfaceOzoneSurfaceless::SwapCompleted(
    const SwapCompletionCallback& callback,
    gfx::SwapResult result) {
  callback.Run(result);
  swap_buffers_pending_ = false;
  if (result == gfx::SwapResult::SWAP_FAILED) {
    last_swap_buffers_result_ = false;
    return;
  }

  SubmitFrame();
}
