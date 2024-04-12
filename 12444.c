  RenderProcessHost* Wait() {
    if (!captured_render_process_host_)
      run_loop_.Run();
    return captured_render_process_host_;
  }
