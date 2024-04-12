void RenderWidgetHostViewAura::AcceleratedSurfacePostSubBuffer(
    const GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params& params_in_pixel,
    int gpu_host_id) {
  gfx::Rect damage_rect(params_in_pixel.x,
                        params_in_pixel.y,
                        params_in_pixel.width,
                        params_in_pixel.height);
  BufferPresentedCallback ack_callback =
      base::Bind(&AcknowledgeBufferForGpu,
                 params_in_pixel.route_id,
                 gpu_host_id,
                 params_in_pixel.mailbox_name);
  BuffersSwapped(params_in_pixel.surface_size,
                 damage_rect,
                 params_in_pixel.surface_scale_factor,
                 params_in_pixel.mailbox_name,
                 params_in_pixel.latency_info,
                 ack_callback);
}
