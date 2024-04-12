void GpuChannel::OnDestroyCommandBuffer(int32 route_id,
                                        IPC::Message* reply_message) {
#if defined(ENABLE_GPU)
  TRACE_EVENT1("gpu", "GpuChannel::OnDestroyCommandBuffer",
               "route_id", route_id);
  if (router_.ResolveRoute(route_id)) {
    GpuCommandBufferStub* stub = stubs_.Lookup(route_id);
    bool need_reschedule = (stub && !stub->IsScheduled());
    gfx::GpuPreference gpu_preference =
        stub ? stub->gpu_preference() : gfx::PreferIntegratedGpu;
    router_.RemoveRoute(route_id);
    stubs_.Remove(route_id);
    if (need_reschedule)
      OnScheduled();
    DidDestroyCommandBuffer(gpu_preference);
  }
#endif

  if (reply_message)
    Send(reply_message);
}
