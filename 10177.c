void WebGL2RenderingContextBase::Trace(blink::Visitor* visitor) {
  visitor->Trace(read_framebuffer_binding_);
  visitor->Trace(transform_feedback_binding_);
  visitor->Trace(default_transform_feedback_);
  visitor->Trace(bound_copy_read_buffer_);
  visitor->Trace(bound_copy_write_buffer_);
  visitor->Trace(bound_pixel_pack_buffer_);
  visitor->Trace(bound_pixel_unpack_buffer_);
  visitor->Trace(bound_transform_feedback_buffer_);
  visitor->Trace(bound_uniform_buffer_);
  visitor->Trace(bound_indexed_uniform_buffers_);
  visitor->Trace(current_boolean_occlusion_query_);
  visitor->Trace(current_transform_feedback_primitives_written_query_);
  visitor->Trace(current_elapsed_query_);
  visitor->Trace(sampler_units_);
  WebGLRenderingContextBase::Trace(visitor);
}
