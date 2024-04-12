  void OnSwapBuffersCompleted(std::vector<ui::LatencyInfo> latency_info,
                              gfx::Size swap_size,
                              const gpu::SwapBuffersCompleteParams& params) {
    client_->DidReceiveSwapBuffersAck();
    swap_buffers_callback_.Run(swap_size);
    UpdateLatencyInfoOnSwap(params.swap_response, &latency_info);
    latency_tracker_.OnGpuSwapBuffersCompleted(latency_info);
  }
