void vp9_free_postproc_buffers(VP9_COMMON *cm) {
#if CONFIG_VP9_POSTPROC
  vpx_free_frame_buffer(&cm->post_proc_buffer);
  vpx_free_frame_buffer(&cm->post_proc_buffer_int);
#else
 (void)cm;
#endif
}
